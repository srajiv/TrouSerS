
/*
 * Licensed Materials - Property of IBM
 *
 * trousers - An open source TCG Software Stack
 *
 * (C) Copyright International Business Machines Corp. 2004
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "trousers/tss.h"
#include "spi_internal_types.h"
#include "tcs_internal_types.h"
#include "tcs_tsp.h"
#include "tcsps.h"
#include "tcs_utils.h"
#include "tcs_int_literals.h"
#include "capabilities.h"
#include "tcslog.h"
#include "req_mgr.h"
#include "tcsd_wrap.h"
#include "tcsd.h"


/*
 * Get a random number generated by the TPM.  Most (all?) TPMs return a maximum number of random
 * bytes that's less than the max allowed to be returned at the TSP level, which is 4K bytes.
 * According to the TPM compliance work posted here: http://www.prosec.rub.de/tpmcompliance.html,
 * some TPMs return as little as 132 bytes per query, which would require about 30 loops to get 4K.
 * We'll be extremely conservative here and loop 50 times, since it won't affect performance on
 * TPMs that return more bytes.
 */
TSS_RESULT
TCSP_GetRandom_Internal(TCS_CONTEXT_HANDLE hContext,	/* in */
			UINT32 * bytesRequested,	/* in, out */
			BYTE ** randomBytes)	/* out */
{
	UINT64 offset;
	TSS_RESULT result;
	UINT32 paramSize, totalReturned = 0, bytesReturned, retries = 50;
	BYTE txBlob[TSS_TPM_TXBLOB_SIZE], *rnd_tmp = NULL;

	LogDebugFn("%u bytes", *bytesRequested);

	if ((result = ctx_verify_context(hContext)))
		return result;

	do {
		offset = 10;
		LoadBlob_UINT32(&offset, *bytesRequested - totalReturned,
				txBlob);
		LoadBlob_Header(TPM_TAG_RQU_COMMAND, offset, TPM_ORD_GetRandom,
				txBlob);

		if ((result = req_mgr_submit_req(txBlob)))
			return result;

		offset = 10;
		result = UnloadBlob_Header(txBlob, &paramSize);
		if (!result) {
			UnloadBlob_UINT32(&offset, &bytesReturned, txBlob);

			LogDebugFn("received %u bytes from the TPM",
				   bytesReturned);

			rnd_tmp = realloc(rnd_tmp, totalReturned + bytesReturned);
			if (rnd_tmp == NULL) {
				LogError("malloc of %d bytes failed.",
					 bytesReturned);
				return TCSERR(TSS_E_OUTOFMEMORY);
			}
			UnloadBlob(&offset, bytesReturned, txBlob, &rnd_tmp[totalReturned]);
			totalReturned += bytesReturned;
		} else {
			free(rnd_tmp);
			return result;
		}
	} while (totalReturned < *bytesRequested && retries--);

	if (totalReturned != *bytesRequested) {
		LogDebugFn("Only %u random bytes recieved from TPM.", totalReturned);
		free(rnd_tmp);
		result = TCSERR(TSS_E_FAIL);
	} else
		*randomBytes = rnd_tmp;

	return result;
}

TSS_RESULT
TCSP_StirRandom_Internal(TCS_CONTEXT_HANDLE hContext,	/* in */
			 UINT32 inDataSize,	/* in */
			 BYTE * inData)	/* in */
{
	UINT64 offset;
	UINT32 paramSize;
	TSS_RESULT result;
	BYTE txBlob[TSS_TPM_TXBLOB_SIZE];

	LogDebug("Entering stir random");

	if ((result = ctx_verify_context(hContext)))
		return result;

	offset = 10;
	LoadBlob_UINT32(&offset, inDataSize, txBlob);
	LoadBlob(&offset, inDataSize, txBlob, inData);
	LoadBlob_Header(TPM_TAG_RQU_COMMAND, offset, TPM_ORD_StirRandom,
			txBlob);

	if ((result = req_mgr_submit_req(txBlob)))
		return result;

	offset = 10;
	result = UnloadBlob_Header(txBlob, &paramSize);
	LogResult("Stir random", result);
	return result;
}

