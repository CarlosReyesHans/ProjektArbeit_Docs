/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
* \addtogroup AxisCommHub_test AxisCommHub_test
* @{
*/

/**
\file AxisCommHub_testObjects
\author ET9300Utilities.ApplicationHandler (Version 1.5.0.0) | EthercatSSC@beckhoff.com

\brief AxisCommHub_test specific objects<br>
\brief NOTE : This file will be overwritten if a new object dictionary is generated!<br>
*/

#if defined(_AXIS_COMM_HUB_TEST_) && (_AXIS_COMM_HUB_TEST_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
/******************************************************************************
*                    Object 0x1600 : MasterCMDs process data mapping
******************************************************************************/
/**
* \addtogroup 0x1600 0x1600 | MasterCMDs process data mapping
* @{
* \brief Object 0x1600 (MasterCMDs process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7000.1<br>
* SubIndex 2 - Reference to 0x7000.2<br>
* SubIndex 3 - Reference to 0x7000.3<br>
* SubIndex 4 - Reference to 0x7000.4<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1600[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x7000.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x7000.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x7000.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex4 - Reference to 0x7000.4 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1600[] = "MasterCMDs process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000\377";
#endif //#ifdef _OBJD_

#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7000.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x7000.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x7000.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x7000.4 */
} OBJ_STRUCT_PACKED_END
TOBJ1600;
#endif //#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1600 MasterCMDsProcessDataMapping0x1600
#if defined(_AXIS_COMM_HUB_TEST_) && (_AXIS_COMM_HUB_TEST_ == 1)
={4,0x70000110,0x70000210,0x70000310,0x70000410}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A00 : Input mapping 0
******************************************************************************/
/**
* \addtogroup 0x1A00 0x1A00 | Input mapping 0
* @{
* \brief Object 0x1A00 (Input mapping 0) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x6000.1<br>
* SubIndex 2 - Reference to 0x6000.2<br>
* SubIndex 3 - Reference to 0x6000.3<br>
* SubIndex 4 - Reference to 0x6000.4<br>
* SubIndex 5 - Reference to 0x6000.5<br>
* SubIndex 6 - Reference to 0x6000.6<br>
* SubIndex 7 - Reference to 0x6000.7<br>
* SubIndex 8 - Reference to 0x6000.8<br>
* SubIndex 9 - Reference to 0x6000.9<br>
* SubIndex 10 - Reference to 0x6000.10<br>
* SubIndex 11 - Reference to 0x6000.11<br>
* SubIndex 12 - Reference to 0x6000.12<br>
* SubIndex 13 - Reference to 0x6000.13<br>
* SubIndex 14 - Reference to 0x6000.14<br>
* SubIndex 15 - Reference to 0x6000.15<br>
* SubIndex 16 - Reference to 0x6001.1<br>
* SubIndex 17 - Reference to 0x6001.2<br>
* SubIndex 18 - Reference to 0x6001.3<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A00[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x6000.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x6000.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x6000.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Reference to 0x6000.4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex5 - Reference to 0x6000.5 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex6 - Reference to 0x6000.6 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex7 - Reference to 0x6000.7 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex8 - Reference to 0x6000.8 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex9 - Reference to 0x6000.9 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex10 - Reference to 0x6000.10 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex11 - Reference to 0x6000.11 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex12 - Reference to 0x6000.12 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex13 - Reference to 0x6000.13 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex14 - Reference to 0x6000.14 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex15 - Reference to 0x6000.15 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex16 - Reference to 0x6001.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex17 - Reference to 0x6001.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex18 - Reference to 0x6001.3 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A00[] = "Input mapping 0\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000"
"SubIndex 007\000"
"SubIndex 008\000"
"SubIndex 009\000"
"SubIndex 010\000"
"SubIndex 011\000"
"SubIndex 012\000"
"SubIndex 013\000"
"SubIndex 014\000"
"SubIndex 015\000"
"SubIndex 016\000"
"SubIndex 017\000"
"SubIndex 018\000\377";
#endif //#ifdef _OBJD_

#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6000.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x6000.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x6000.3 */
UINT32 SI4; /* Subindex4 - Reference to 0x6000.4 */
UINT32 SI5; /* Subindex5 - Reference to 0x6000.5 */
UINT32 SI6; /* Subindex6 - Reference to 0x6000.6 */
UINT32 SI7; /* Subindex7 - Reference to 0x6000.7 */
UINT32 SI8; /* Subindex8 - Reference to 0x6000.8 */
UINT32 SI9; /* Subindex9 - Reference to 0x6000.9 */
UINT32 SI10; /* Subindex10 - Reference to 0x6000.10 */
UINT32 SI11; /* Subindex11 - Reference to 0x6000.11 */
UINT32 SI12; /* Subindex12 - Reference to 0x6000.12 */
UINT32 SI13; /* Subindex13 - Reference to 0x6000.13 */
UINT32 SI14; /* Subindex14 - Reference to 0x6000.14 */
UINT32 SI15; /* Subindex15 - Reference to 0x6000.15 */
UINT32 SI16; /* Subindex16 - Reference to 0x6001.1 */
UINT32 SI17; /* Subindex17 - Reference to 0x6001.2 */
UINT32 SI18; /* Subindex18 - Reference to 0x6001.3 */
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif //#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 InputMapping00x1A00
#if defined(_AXIS_COMM_HUB_TEST_) && (_AXIS_COMM_HUB_TEST_ == 1)
={18,0x60000110,0x60000210,0x60000310,0x60000410,0x60000510,0x60000610,0x60000710,0x60000810,0x60000910,0x60000A10,0x60000B10,0x60000C10,0x60000D10,0x60000E10,0x60000F10,0x60010110,0x60010210,0x60010310}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C12 : SyncManager 2 assignment
******************************************************************************/
/**
* \addtogroup 0x1C12 0x1C12 | SyncManager 2 assignment
* @{
* \brief Object 0x1C12 (SyncManager 2 assignment) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C12[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C12[] = "SyncManager 2 assignment\000\377";
#endif //#ifdef _OBJD_

#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif //#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C12 sRxPDOassign
#if defined(_AXIS_COMM_HUB_TEST_) && (_AXIS_COMM_HUB_TEST_ == 1)
={1,{0x1600}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C13 : SyncManager 3 assignment
******************************************************************************/
/**
* \addtogroup 0x1C13 0x1C13 | SyncManager 3 assignment
* @{
* \brief Object 0x1C13 (SyncManager 3 assignment) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C13[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C13[] = "SyncManager 3 assignment\000\377";
#endif //#ifdef _OBJD_

#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif //#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C13 sTxPDOassign
#if defined(_AXIS_COMM_HUB_TEST_) && (_AXIS_COMM_HUB_TEST_ == 1)
={1,{0x1A00}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6000 : Temperature
******************************************************************************/
/**
* \addtogroup 0x6000 0x6000 | Temperature
* @{
* \brief Object 0x6000 (Temperature) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - TEMPERATURE0<br>
* SubIndex 2 - TEMPERATURE1<br>
* SubIndex 3 - TEMPERATURE2<br>
* SubIndex 4 - TEMPERATURE3<br>
* SubIndex 5 - TEMPERATURE4<br>
* SubIndex 6 - TEMPERATURE5<br>
* SubIndex 7 - TEMPERATURE6<br>
* SubIndex 8 - TEMPERATURE7<br>
* SubIndex 9 - TEMPERATURE8<br>
* SubIndex 10 - TEMPERATURE9<br>
* SubIndex 11 - TEMPERATURE10<br>
* SubIndex 12 - TEMPERATURE11<br>
* SubIndex 13 - TEMPERATURE12<br>
* SubIndex 14 - TEMPERATURE13<br>
* SubIndex 15 - TEMPERATURE14<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - TEMPERATURE0 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - TEMPERATURE1 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - TEMPERATURE2 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex4 - TEMPERATURE3 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex5 - TEMPERATURE4 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex6 - TEMPERATURE5 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex7 - TEMPERATURE6 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex8 - TEMPERATURE7 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex9 - TEMPERATURE8 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex10 - TEMPERATURE9 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex11 - TEMPERATURE10 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex12 - TEMPERATURE11 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex13 - TEMPERATURE12 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex14 - TEMPERATURE13 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }}; /* Subindex15 - TEMPERATURE14 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6000[] = "Temperature\000"
"TEMPERATURE0\000"
"TEMPERATURE1\000"
"TEMPERATURE2\000"
"TEMPERATURE3\000"
"TEMPERATURE4\000"
"TEMPERATURE5\000"
"TEMPERATURE6\000"
"TEMPERATURE7\000"
"TEMPERATURE8\000"
"TEMPERATURE9\000"
"TEMPERATURE10\000"
"TEMPERATURE11\000"
"TEMPERATURE12\000"
"TEMPERATURE13\000"
"TEMPERATURE14\000\377";
#endif //#ifdef _OBJD_

#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 TEMPERATURE0; /* Subindex1 - TEMPERATURE0 */
UINT16 TEMPERATURE1; /* Subindex2 - TEMPERATURE1 */
UINT16 TEMPERATURE2; /* Subindex3 - TEMPERATURE2 */
UINT16 TEMPERATURE3; /* Subindex4 - TEMPERATURE3 */
UINT16 TEMPERATURE4; /* Subindex5 - TEMPERATURE4 */
UINT16 TEMPERATURE5; /* Subindex6 - TEMPERATURE5 */
UINT16 TEMPERATURE6; /* Subindex7 - TEMPERATURE6 */
UINT16 TEMPERATURE7; /* Subindex8 - TEMPERATURE7 */
UINT16 TEMPERATURE8; /* Subindex9 - TEMPERATURE8 */
UINT16 TEMPERATURE9; /* Subindex10 - TEMPERATURE9 */
UINT16 TEMPERATURE10; /* Subindex11 - TEMPERATURE10 */
UINT16 TEMPERATURE11; /* Subindex12 - TEMPERATURE11 */
UINT16 TEMPERATURE12; /* Subindex13 - TEMPERATURE12 */
UINT16 TEMPERATURE13; /* Subindex14 - TEMPERATURE13 */
UINT16 TEMPERATURE14; /* Subindex15 - TEMPERATURE14 */
} OBJ_STRUCT_PACKED_END
TOBJ6000;
#endif //#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6000 Temperature0x6000
#if defined(_AXIS_COMM_HUB_TEST_) && (_AXIS_COMM_HUB_TEST_ == 1)
={15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6001 : SystemStatus
******************************************************************************/
/**
* \addtogroup 0x6001 0x6001 | SystemStatus
* @{
* \brief Object 0x6001 (SystemStatus) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - STATUS<br>
* SubIndex 2 - EVENT<br>
* SubIndex 3 - ERROR<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6001[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - STATUS */
{ DEFTYPE_INTEGER16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - EVENT */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }}; /* Subindex3 - ERROR */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6001[] = "SystemStatus\000"
"STATUS\000"
"EVENT\000"
"ERROR\000\377";
#endif //#ifdef _OBJD_

#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 STATUS; /* Subindex1 - STATUS */
INT16 EVENT; /* Subindex2 - EVENT */
UINT16 ERROR; /* Subindex3 - ERROR */
} OBJ_STRUCT_PACKED_END
TOBJ6001;
#endif //#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6001 SystemStatus0x6001
#if defined(_AXIS_COMM_HUB_TEST_) && (_AXIS_COMM_HUB_TEST_ == 1)
={3,0,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7000 : MasterCMDs
******************************************************************************/
/**
* \addtogroup 0x7000 0x7000 | MasterCMDs
* @{
* \brief Object 0x7000 (MasterCMDs) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - COMMAND<br>
* SubIndex 2 - TEST VALUE0<br>
* SubIndex 3 - TEST VALUE1<br>
* SubIndex 4 - TEST VALUE2<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - COMMAND */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex2 - TEST VALUE0 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex3 - TEST VALUE1 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex4 - TEST VALUE2 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7000[] = "MasterCMDs\000"
"COMMAND\000"
"TEST VALUE0\000"
"TEST VALUE1\000"
"TEST VALUE2\000\377";
#endif //#ifdef _OBJD_

#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 COMMAND; /* Subindex1 - COMMAND */
UINT16 TESTVALUE0; /* Subindex2 - TEST VALUE0 */
UINT16 TESTVALUE1; /* Subindex3 - TEST VALUE1 */
UINT16 TESTVALUE2; /* Subindex4 - TEST VALUE2 */
} OBJ_STRUCT_PACKED_END
TOBJ7000;
#endif //#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7000 MasterCMDs0x7000
#if defined(_AXIS_COMM_HUB_TEST_) && (_AXIS_COMM_HUB_TEST_ == 1)
={4,0,0,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0xF000 : Modular Device Profile
******************************************************************************/
/**
* \addtogroup 0xF000 0xF000 | Modular Device Profile
* @{
* \brief Object 0xF000 (Modular Device Profile) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Index distance <br>
* SubIndex 2 - Maximum number of modules <br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0xF000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }, /* Subindex1 - Index distance  */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }}; /* Subindex2 - Maximum number of modules  */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0xF000[] = "Modular Device Profile\000"
"Index distance \000"
"Maximum number of modules \000\377";
#endif //#ifdef _OBJD_

#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 IndexDistance; /* Subindex1 - Index distance  */
UINT16 MaximumNumberOfModules; /* Subindex2 - Maximum number of modules  */
} OBJ_STRUCT_PACKED_END
TOBJF000;
#endif //#ifndef _AXIS_COMM_HUB_TEST_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJF000 ModularDeviceProfile0xF000
#if defined(_AXIS_COMM_HUB_TEST_) && (_AXIS_COMM_HUB_TEST_ == 1)
={2,0x0010,0}
#endif
;
/** @}*/







#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1600 */
{NULL , NULL ,  0x1600 , {DEFTYPE_PDOMAPPING , 4 | (OBJCODE_REC << 8)} , asEntryDesc0x1600 , aName0x1600 , &MasterCMDsProcessDataMapping0x1600 , NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 18 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &InputMapping00x1A00 , NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x6000 */
{NULL , NULL ,  0x6000 , {DEFTYPE_RECORD , 15 | (OBJCODE_REC << 8)} , asEntryDesc0x6000 , aName0x6000 , &Temperature0x6000 , NULL , NULL , 0x0000 },
/* Object 0x6001 */
{NULL , NULL ,  0x6001 , {DEFTYPE_RECORD , 3 | (OBJCODE_REC << 8)} , asEntryDesc0x6001 , aName0x6001 , &SystemStatus0x6001 , NULL , NULL , 0x0000 },
/* Object 0x7000 */
{NULL , NULL ,  0x7000 , {DEFTYPE_RECORD , 4 | (OBJCODE_REC << 8)} , asEntryDesc0x7000 , aName0x7000 , &MasterCMDs0x7000 , NULL , NULL , 0x0000 },
/* Object 0xF000 */
{NULL , NULL ,  0xF000 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0xF000 , aName0xF000 , &ModularDeviceProfile0xF000 , NULL , NULL , 0x0000 },
{NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_
#undef PROTO

/** @}*/
#define _AXIS_COMM_HUB_TEST_OBJECTS_H_
