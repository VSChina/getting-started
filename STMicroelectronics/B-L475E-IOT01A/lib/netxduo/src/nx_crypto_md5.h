/**************************************************************************/
/*                                                                        */
/*            Copyright (c) 1996-2019 by Express Logic Inc.               */
/*                                                                        */
/*  This software is copyrighted by and is the sole property of Express   */
/*  Logic, Inc.  All rights, title, ownership, or other interests         */
/*  in the software remain the property of Express Logic, Inc.  This      */
/*  software may only be used in accordance with the corresponding        */
/*  license agreement.  Any unauthorized use, duplication, transmission,  */
/*  distribution, or disclosure of this software is expressly forbidden.  */
/*                                                                        */
/*  This Copyright notice may not be removed or modified without prior    */
/*  written consent of Express Logic, Inc.                                */
/*                                                                        */
/*  Express Logic, Inc. reserves the right to modify this software        */
/*  without notice.                                                       */
/*                                                                        */
/*  Express Logic, Inc.                     info@expresslogic.com         */
/*  11423 West Bernardo Court               http://www.expresslogic.com   */
/*  San Diego, CA  92127                                                  */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/*
  Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
  rights reserved.

  License to copy and use this software is granted provided that it
  is identified as the ""RSA Data Security, Inc. MD5 Message-Digest
  Algorithm"" in all material mentioning or referencing this software
  or this function.

  License is also granted to make and use derivative works provided
  that such works are identified as ""derived from the RSA Data
  Security, Inc. MD5 Message-Digest Algorithm"" in all material
  mentioning or referencing the derived work.

  RSA Data Security, Inc. makes no representations concerning either
  the merchantability of this software or the suitability of this
  software for any particular purpose. It is provided ""as is""
  without express or implied warranty of any kind.

  These notices must be retained in any copies of any part of this
  documentation and/or software.
*/
/**************************************************************************/

/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** NetX Crypto Component                                                 */
/**                                                                       */
/**   MD5 Digest Algorithm (MD5)                                          */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/**************************************************************************/
/*                                                                        */
/*  COMPONENT DEFINITION                                   RELEASE        */
/*                                                                        */
/*    nx_md5.h                                            PORTABLE C      */
/*                                                           5.12         */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Express Logic, Inc.                                 */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This file defines the NetX MD5 algorithm, derived principally from  */
/*    RFC1321.                                                            */
/*                                                                        */
/*    It is assumed that nx_api.h and nx_port.h have already been         */
/*    included.                                                           */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  12-15-2017     Timothy Stapko           Initial Version 5.11          */
/*  08-15-2019     Timothy Stapko           Modified comment(s),          */
/*                                            added logic so NetX Crypto  */
/*                                            is FIPS 140-2 compliant,    */
/*                                            add C++ extern wrapper,     */
/*                                            fixed the compiler error for*/
/*                                            cast-function-type,         */
/*                                            resulting in version 5.12   */
/*                                                                        */
/**************************************************************************/

#ifndef  NX_MD5_H
#define  NX_MD5_H

/* Determine if a C++ compiler is being used.  If so, ensure that standard
   C is used to process the API information.  */
#ifdef __cplusplus

/* Yes, C++ compiler is present.  Use standard C.  */
extern   "C" {

#endif

#include "nx_crypto.h"

#define NX_CRYPTO_MD5_BLOCK_SIZE_IN_BYTES   64
#define NX_CRYPTO_MD5_ICV_LEN_IN_BITS       128

/* Define the control block structure for backward compatibility. */
#define NX_MD5                                  NX_CRYPTO_MD5

/* Define the MD5 context structure.  */

typedef struct NX_CRYPTO_MD5_STRUCT
{

    ULONG nx_md5_states[4];                             /* Contains each state (A,B,C,D)    */
    ULONG nx_md5_bit_count[2];                          /* Contains the 64-bit total bit    */
                                                        /*   count, where index 0 holds the */
                                                        /*   least significant bit count and*/
                                                        /*   index 1 contains the most      */
                                                        /*   significant portion of the bit */
                                                        /*   count                          */
    UCHAR nx_md5_buffer[64];                            /* Working buffer for MD5 algorithm */
                                                        /*   where partial buffers are      */
                                                        /*   accumulated until a full block */
                                                        /*   can be processed               */
} NX_CRYPTO_MD5;


/* Define the function prototypes for MD5.  */

UINT _nx_crypto_md5_initialize(NX_CRYPTO_MD5 *context, UINT algorithm);
UINT _nx_crypto_md5_update(NX_CRYPTO_MD5 *context, UCHAR *input_ptr, UINT input_length);
UINT _nx_crypto_md5_digest_calculate(NX_CRYPTO_MD5 * context, UCHAR digest[16], UINT algorithm);
VOID _nx_crypto_md5_process_buffer(NX_CRYPTO_MD5 * context, UCHAR buffer[64]);

UINT _nx_crypto_method_md5_init(struct  NX_CRYPTO_METHOD_STRUCT *method,
                                UCHAR *key, NX_CRYPTO_KEY_SIZE key_size_in_bits,
                                VOID  **handle,
                                VOID  *crypto_metadata,
                                ULONG crypto_metadata_size);

UINT _nx_crypto_method_md5_cleanup(VOID *crypto_metadata);

UINT _nx_crypto_method_md5_operation(UINT op,      /* Encrypt, Decrypt, Authenticate */
                                     VOID *handle, /* Crypto handler */
                                     struct NX_CRYPTO_METHOD_STRUCT *method,
                                     UCHAR *key, NX_CRYPTO_KEY_SIZE key_size_in_bits,
                                     UCHAR *input, ULONG input_length_in_byte,
                                     UCHAR *iv_ptr,
                                     UCHAR *output, ULONG output_length_in_byte,
                                     VOID *crypto_metadata, ULONG crypto_metadata_size,
                                     VOID *packet_ptr,
                                     VOID (*nx_crypto_hw_process_callback)(VOID *packet_ptr, UINT status));
#endif


#ifdef __cplusplus
}
#endif
