/*-----------------------------------------------------------------------------------
| File Name   :   Det.c
| Project Name:   ������Դ��-MC9S12XEP100 DET����
| Author      :   ������
| Affiliation :   Chongqing University of Posts and Telecommunications
|                 �˸߻�����3-2 �����Ŷ�
|
| Description :   DETģ������Դ����
| Version     :   1.0 7-11-2009
|------------------------------------------------------------------------------------
| Copyright (c)  2009-2010 by CQUPT  All rights reserved.
|----------------------------------------------------------------------------------*/

/*
***************************************************************************************
*   INCLUDES
***************************************************************************************
*/
#include "Det.h"
#include "SchM_Det.h"
#include "Dlt.h"

/*
***************************************************************************************
*     Gobal variables
***************************************************************************************
*/

uint8 Det_Init_Status;//DET��ʼ��״̬��־λ
Det_ErrorBufferType Error_Report[BUFF_NUM];//����ֵ�洢
uint16 Error_Counter=0;
boolean Det_Enbale;//ʹ�ܱ�־

/*
****************************************************************************************
@Function:    Det_Init
----------------------------------------------------------------------------------------
@Parameters:  None
----------------------------------------------------------------------------------------
@Returnvalue: None
----------------------------------------------------------------------------------------
@Description: This Function initialize the DET module 
****************************************************************************************
*/

void Det_Init(void)
{
	uint16 i;
	for(i=0;i<BUFF_NUM;i++)
	{
	  //Error_Report[i]=0;//�������ֵ
		Error_Report[i].ModuleId=0;
		Error_Report[i].InstanceId=0;
		Error_Report[i].ApiId=0;
		Error_Report[i].ErrorId=0;
	}
	Error_Counter=0;
	Det_Init_Status=DET_INIT;//��ʼ�����
}


/*
****************************************************************************************
@Function:    Det_ReportError
----------------------------------------------------------------------------------------
@Parameters:  ModuleId:     which module the error occured 
              InstanceId:   which instance the error occured
              ApiId:        which function the error occured
              ErrorId:      what kind of error has been occured
----------------------------------------------------------------------------------------
@Returnvalue: E_NOT_OK: The error has been occured.
----------------------------------------------------------------------------------------
@Description: This Function send the development error report
****************************************************************************************
*/

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
  uint16 j;//&& Det_Init_Status!=DET_INIT
	if(Det_Enbale!=STD_ON)
	{
	   return(E_NOT_OK);//û�б���ʼ�������Ǵ����Ѿ�����
	}
	else
	{
		j=Error_Counter++;
		Error_Report[j].ModuleId=(uint16)ModuleId;
		Error_Report[j].InstanceId=(uint8)InstanceId;
		Error_Report[j].ApiId=(uint8)ApiId;
		Error_Report[j].ErrorId=(uint8)ErrorId;
		return(E_NOT_OK);//��¼����
	}
}

/*
****************************************************************************************
@Function:    Det_Start
----------------------------------------------------------------------------------------
@Parameters:  None
----------------------------------------------------------------------------------------
@Returnvalue: None
----------------------------------------------------------------------------------------
@Description: This Function start the development error trancer
****************************************************************************************
*/

void Det_Start(void)
{
	if(Det_Init_Status==DET_INIT)//����Ƿ��ʼ��
	{
     Det_Enbale=STD_ON;//�����豸���������
  }
	else
	{
	  ;
	}
}

/*
****************************************************************************************
@Function:    Det_GetVersionInfo
----------------------------------------------------------------------------------------
@Parameters:  Pinter to Version information
----------------------------------------------------------------------------------------
@Returnvalue: None
----------------------------------------------------------------------------------------
@Description: This Function gets the version informations of DET 
****************************************************************************************
*/

#if (DET_VERSION_INFO_API==STD_ON)
void Det_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
	(versioninfo)->vendorID         = (uint16)DET_VENDOR_ID;
	(versioninfo)->moduleID         = (uint16)DET_MODULE_ID;
	(versioninfo)->sw_major_version = (uint8)DET_SW_MAJOR_VERSION;
	(versioninfo)->sw_minor_version = (uint8)DET_SW_MINOR_VERSION;
	(versioninfo)->sw_patch_version = (uint8)DET_SW_PATCH_VERSION;
    
}
#endif

/**************************************************************************************/