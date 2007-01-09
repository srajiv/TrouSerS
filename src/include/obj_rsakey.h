
/*
 * Licensed Materials - Property of IBM
 *
 * trousers - An open source TCG Software Stack
 *
 * (C) Copyright International Business Machines Corp. 2004-2006
 *
 */

#ifndef _OBJ_RSAKEY_H_
#define _OBJ_RSAKEY_H_

#ifdef TSS_BUILD_RSAKEY_LIST

/* structures */
struct tr_rsakey_obj {
	int type;
	struct {
		union {
			struct {
				TPM_VERSION ver;
			} key11;
			struct {
				TPM_STRUCTURE_TAG tag;
				UINT16 fill;
			} key12;
		} u;
		TPM_KEY_USAGE keyUsage;
		TPM_KEY_FLAGS keyFlags;
		TPM_AUTH_DATA_USAGE authDataUsage;
		TPM_KEY_PARMS algorithmParms;
		UINT32 PCRInfoSize;
		BYTE *PCRInfo;
		TPM_STORE_PUBKEY pubKey;
		UINT32 encSize;
		BYTE *encData;
	} key;
	TSS_HPOLICY usagePolicy;
	TSS_HPOLICY migPolicy;
	TSS_UUID uuid;
	TCS_KEY_HANDLE tcsHandle;
};

/* obj_rsakey.c */
void       obj_list_rsakey_close(struct obj_list *, TSS_HCONTEXT);
TSS_BOOL   obj_is_rsakey(TSS_HOBJECT);
TSS_RESULT obj_rsakey_add(TSS_HCONTEXT, TSS_FLAG, TSS_HOBJECT *);
TSS_RESULT obj_rsakey_add_by_key(TSS_HCONTEXT, TSS_UUID *, BYTE *, TSS_FLAG, TSS_HKEY *);
TSS_RESULT obj_rsakey_set_policy(TSS_HKEY, UINT32, TSS_HPOLICY);
TSS_RESULT obj_rsakey_remove(TSS_HOBJECT, TSS_HCONTEXT);
TSS_RESULT obj_rsakey_get_tsp_context(TSS_HKEY, TSS_HCONTEXT *);
TSS_RESULT obj_rsakey_set_pstype(TSS_HKEY, UINT32);
TSS_RESULT obj_rsakey_get_pstype(TSS_HKEY, UINT32 *);
TSS_RESULT obj_rsakey_get_usage(TSS_HKEY, UINT32 *);
TSS_RESULT obj_rsakey_set_usage(TSS_HKEY, UINT32);
TSS_RESULT obj_rsakey_set_migratable(TSS_HKEY, UINT32);
TSS_RESULT obj_rsakey_set_redirected(TSS_HKEY, UINT32);
TSS_RESULT obj_rsakey_set_volatile(TSS_HKEY, UINT32);
TSS_RESULT obj_rsakey_get_authdata_usage(TSS_HKEY, UINT32 *);
TSS_RESULT obj_rsakey_set_authdata_usage(TSS_HKEY, UINT32);
TSS_RESULT obj_rsakey_get_alg(TSS_HKEY, UINT32 *);
TSS_RESULT obj_rsakey_set_alg(TSS_HKEY, UINT32);
TSS_RESULT obj_rsakey_get_es(TSS_HKEY, UINT32 *);
TSS_RESULT obj_rsakey_set_es(TSS_HKEY, UINT32);
TSS_RESULT obj_rsakey_get_ss(TSS_HKEY, UINT32 *);
TSS_RESULT obj_rsakey_set_ss(TSS_HKEY, UINT32);
TSS_RESULT obj_rsakey_set_num_primes(TSS_HKEY, UINT32);
TSS_RESULT obj_rsakey_get_num_primes(TSS_HKEY, UINT32 *);
TSS_RESULT obj_rsakey_set_flags(TSS_HKEY, UINT32);
TSS_RESULT obj_rsakey_get_flags(TSS_HKEY, UINT32 *);
TSS_RESULT obj_rsakey_set_size(TSS_HKEY, UINT32);
TSS_RESULT obj_rsakey_get_size(TSS_HKEY, UINT32 *);
TSS_BOOL   obj_rsakey_is_migratable(TSS_HKEY);
TSS_BOOL   obj_rsakey_is_redirected(TSS_HKEY);
TSS_BOOL   obj_rsakey_is_volatile(TSS_HKEY);
TSS_RESULT obj_rsakey_get_policy(TSS_HKEY, TSS_FLAG, TSS_HPOLICY *, TSS_BOOL *);
TSS_RESULT obj_rsakey_get_blob(TSS_HKEY, UINT32 *, BYTE **);
TSS_RESULT obj_rsakey_get_priv_blob(TSS_HKEY, UINT32 *, BYTE **);
TSS_RESULT obj_rsakey_get_pub_blob(TSS_HKEY, UINT32 *, BYTE **);
TSS_RESULT obj_rsakey_get_version(TSS_HKEY, UINT32 *, BYTE **);
TSS_RESULT obj_rsakey_get_exponent(TSS_HKEY, UINT32 *, BYTE **);
TSS_RESULT obj_rsakey_set_exponent(TSS_HKEY, UINT32, BYTE *);
TSS_RESULT obj_rsakey_get_modulus(TSS_HKEY, UINT32 *, BYTE **);
TSS_RESULT obj_rsakey_set_modulus(TSS_HKEY, UINT32, BYTE *);
TSS_RESULT obj_rsakey_get_uuid(TSS_HKEY, UINT32 *, BYTE **);
TSS_RESULT obj_rsakey_get_parent_uuid(TSS_HKEY, TSS_FLAG *, TSS_UUID *);
TSS_RESULT obj_rsakey_set_uuids(TSS_HKEY, TSS_FLAG, TSS_UUID *, TSS_FLAG, TSS_UUID *);
TSS_RESULT obj_rsakey_set_uuid(TSS_HKEY, TSS_FLAG, TSS_UUID *);
TSS_RESULT obj_rsakey_set_tcpakey(TSS_HKEY, UINT32 , BYTE *);
TSS_RESULT obj_rsakey_get_pcr_atcreation(TSS_HKEY, UINT32 *, BYTE **);
TSS_RESULT obj_rsakey_get_pcr_atrelease(TSS_HKEY, UINT32 *, BYTE **);
TSS_RESULT obj_rsakey_get_pcr_selection(TSS_HKEY, UINT32 *, BYTE **);
TSS_RESULT obj_rsakey_set_pubkey(TSS_HKEY, BYTE *);
TSS_RESULT obj_rsakey_set_privkey(TSS_HKEY, UINT32 , BYTE *);
TSS_RESULT obj_rsakey_set_pcr_data(TSS_HKEY, TSS_HPOLICY);
TSS_RESULT obj_rsakey_set_key_parms(TSS_HKEY, TCPA_KEY_PARMS *);
TSS_RESULT obj_rsakey_is_connected(TSS_HKEY, TCS_CONTEXT_HANDLE *);
TSS_RESULT obj_rsakey_get_by_uuid(TSS_UUID *, TSS_HKEY *);
TSS_RESULT obj_rsakey_get_by_pub(UINT32, BYTE *, TSS_HKEY *);
TSS_RESULT obj_rsakey_get_tcs_handle(TSS_HKEY, TCS_KEY_HANDLE *);
TSS_RESULT obj_rsakey_set_tcs_handle(TSS_HKEY, TCS_KEY_HANDLE);

#define RSAKEY_LIST_DECLARE		struct obj_list rsakey_list
#define RSAKEY_LIST_DECLARE_EXTERN	extern struct obj_list rsakey_list
#define RSAKEY_LIST_INIT()		list_init(&rsakey_list)
#define RSAKEY_LIST_CONNECT(a,b)	obj_connectContext_list(&rsakey_list, a, b)
#define RSAKEY_LIST_CLOSE(a)		obj_list_rsakey_close(&rsakey_list, a)

#else

#define obj_is_rsakey(a)	FALSE

#define RSAKEY_LIST_DECLARE
#define RSAKEY_LIST_DECLARE_EXTERN
#define RSAKEY_LIST_INIT()
#define RSAKEY_LIST_CONNECT(a,b)
#define RSAKEY_LIST_CLOSE(a)

#endif

#endif