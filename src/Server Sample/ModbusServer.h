'!TITLE "ModBus - Public Variables"

'RC8 Option - Modbus Provider------------------------------------------------
' @file    ModbusServer.h
' @brief   Modbus Constant Define.
' @details Variable Masking of Modbus data types. 
'
' @version 1.0.1
' @date    2016/05/02
' @author  Carlos A. Lopez (DPAM - R&D)	
'
' Software License Agreement (MIT License)
'
' @copyright Copyright (c) 2019 DENSO 2DLab
'
' Permission is hereby granted, free of charge, to any person obtaining a copy
' of this software and associated documentation files (the "Software"), to deal
' in the Software without restriction, including without limitation the rights
' to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
' copies of the Software, and to permit persons to whom the Software is
' furnished to do so, subject to the following conditions:
'
' The above copyright notice and this permission notice shall be included in
' all copies or substantial portions of the Software.
'
' THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
' IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
' FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
' AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
' LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
' OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
' THE SOFTWARE.
'-------------------------------------------------------------------------------

#Include "Variant.h"

'Modbus Memory Map
#DEFINE MEM_ARRAY_SIZE 			65536

'Function Codes
#DEFINE READ_COILS					&h01			
#DEFINE READ_DISCRETE_INPUTS		&h02
#DEFINE READ_HOLDING_REGISTERS		&h03
#DEFINE READ_INPUT_REGISTERS		&h04
#DEFINE WRITE_SINGLE_COIL			&h05		'Not Supported
#DEFINE WRITE_SINGLE_REGISTER		&h06		'Not Supported
#DEFINE READ_EXCEPTION_STATUS		&h07
#DEFINE WRITE_MULTIPLE_COILS		&h0F
#DEFINE WRITE_MULTIPLE_REGISTERS	&h10

'Error Code Constants
#DEFINE ILLEGAL_FUNCTION 						&h01
#DEFINE ILLEGAL_DATA_ADDRESS 					&h02
#DEFINE ILLEGAL_DATA_VALUE						&h03
#DEFINE SERVER_DEVICE_FAILURE					&h04
#DEFINE ACKNOWLEDGE								&h05
#DEFINE SERVER_DEVICE_BUSY						&h06
#DEFINE MEMORY_PARITY_ERROR						&h08
#DEFINE GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND	&h0B
#DEFINE GATEWAY_PATH_UNAVAILABLE 				&h0A

'Exeception Code (Error)
'Code	|	Name					|	Meaning
'01			ILLEGAL FUNCTION			The function code received in the query is not 
'										an allowable action for the server. This may 
'										be because the function code is only applicable 
'										to newer devices, and was not implemented in the 
'										unit selected. It could also indicate that the 
'										server is in the wrong state to process a request 
'										of this type, for example because it is unconfigured 
'										and is being asked to return register values.
'
'02			ILLEGAL DATA ADDRESS		The data address received in the query is not an 
'										allowable address for the server. More specifically, 
'										the combination of reference number and transfer length 
'										is invalid. For a controller with 100 registers, the PDU 
'										addresses the first register as 0, and the last one as 99. 
'										If a request is submitted with a starting register address 
'										of 96 and a quantity of registers of 4, then this request 
'										will successfully operate (address-wise at least) on registers 
'										96, 97, 98, 99. If a request is submitted with a starting 
'										register address of 96 and a quantity of registers of 5, 
'										then this request will fail with Exception Code 0x02 “Illegal 
'										Data Address” since it attempts to operate on registers 96, 97,
'										98, 99 and 100, and there is no register with address 100.
'
'03			ILLEGAL DATA VALUE			A value contained in the query data field is not an allowable 
'										value for server. This indicates a fault in the structure of 
'										the remainder of a complex request, such as that the implied 
'										length is incorrect. It specifically does NOT mean that a data 
'										item submitted for storage in a register has a value outside the 
'										expectation of the application program, since the MODBUS protocol 
'										is unaware of the significance of any particular value of any 
'										particular register.
'
'04			SERVER DEVICE FAILURE		An unrecoverable error occurred while the server was attempting 
'										to perform the requested action.
'
'05			ACKNOWLEDGE					Specialized use in conjunction with programming commands.
'										The server has accepted the request and is processing it, 
'										but a long duration of time will be required to do so. This	
'										response is returned to prevent a timeout error from occurring in 
'										the client. The client can next issue a Poll Program Complete 
'										message to determine if processing is completed.
'
'06			SERVER DEVICE BUSY			Specialized use in conjunction with programming commands.
'										The server is engaged in processing a long–duration program command. 
'										The client should retransmit the message later when the server is free.
'
'08			MEMORY PARITY ERROR			Specialized use in conjunction with function codes 20 and 21 and 
'										reference type 6, to indicate that the extended file area failed to pass 
'										a consistency check.
'										The server attempted to read record file, but detected a parity error in 
'										the memory. The client can retry the request, but service may be required.
'
'0A			GATEWAY PATH UNAVAILABLE	Specialized use in conjunction with gateways, indicates that the gateway 
'										was unable to allocate an internal communication path from the input port 
'										to the output port for processing the request. Usually means that the 
'										gateway is misconfigured or overloaded.	
'
'0B			GATEWAY TARGET DEVICE		Specialized use in conjunction with gateways, indicates that no response 
'			FAILED TO RESPOD			was obtained from the target device. Usually means that the device is not 
'										present on the network.


'ModBus Data Tables
'------------------------------------------------------------------------------
'Discrete Input
'Object Type: Single Bit
'Type Of: Read-Only
'Comment: This type of data can be provided by an I/O System
Dim DiscreteInputs(MEM_ARRAY_SIZE - 1) As Integer

'Coils
'Object Type: Single Bit
'Type Of: Read-Write
'Comments: This type of data can be alterable by an application program
Dim Coils(MEM_ARRAY_SIZE - 1) As Integer

'Input Registers
'Object Type: 16-bit Word
'Type Of: Read-Only
'Comments: This type of data can be provided by an I/O system
Dim InputRegisters(MEM_ARRAY_SIZE - 1) As Integer

'Holding Registers
'Object Type: 16-bit Word
'Type Of: Read-Write
'Comments: This type of data can be alterate by an application program
Dim HoldingRegisters(MEM_ARRAY_SIZE - 1) As Integer

'Exception Code
'Object Type: Byte
Dim ExceptionCode As Integer
'------------------------------------------------------------------------------


'ORiN2 Modbus Provider
'------------------------------------------------------------------------------
Dim caoCtrl As Object


'Modbus Register Table Mapping to RC8 I/O
'------------------------------------------------------------------------------
#Include "DataDefinition.pcs"
