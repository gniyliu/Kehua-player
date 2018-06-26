

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Jun 24 21:31:54 2018
 */
/* Compiler settings for MyTest.odl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __MyTest_h_h__
#define __MyTest_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMyTest_FWD_DEFINED__
#define __IMyTest_FWD_DEFINED__
typedef interface IMyTest IMyTest;
#endif 	/* __IMyTest_FWD_DEFINED__ */


#ifndef __MyTest_FWD_DEFINED__
#define __MyTest_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyTest MyTest;
#else
typedef struct MyTest MyTest;
#endif /* __cplusplus */

#endif 	/* __MyTest_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MyTest_LIBRARY_DEFINED__
#define __MyTest_LIBRARY_DEFINED__

/* library MyTest */
/* [version][uuid] */ 


DEFINE_GUID(LIBID_MyTest,0x633E2850,0xDEF3,0x445A,0x91,0xD7,0x05,0x78,0xC1,0x7D,0x34,0x14);

#ifndef __IMyTest_DISPINTERFACE_DEFINED__
#define __IMyTest_DISPINTERFACE_DEFINED__

/* dispinterface IMyTest */
/* [uuid] */ 


DEFINE_GUID(DIID_IMyTest,0x20D8C2DE,0x92A1,0x48C5,0xA3,0x05,0xF4,0x14,0xB3,0xC2,0xEC,0x34);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("20D8C2DE-92A1-48C5-A305-F414B3C2EC34")
    IMyTest : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMyTestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyTest * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyTest * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMyTest * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMyTest * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMyTest * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMyTest * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IMyTestVtbl;

    interface IMyTest
    {
        CONST_VTBL struct IMyTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyTest_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMyTest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMyTest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMyTest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMyTest_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_MyTest,0xE558AC74,0xB803,0x4F71,0x8A,0x5C,0x22,0x16,0x87,0xC0,0xEC,0xDF);

#ifdef __cplusplus

class DECLSPEC_UUID("E558AC74-B803-4F71-8A5C-221687C0ECDF")
MyTest;
#endif
#endif /* __MyTest_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


