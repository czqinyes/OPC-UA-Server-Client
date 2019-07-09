// OPCClientTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include "open62541.h"

int main(void)
{
	UA_Client *client = UA_Client_new(UA_ClientConfig_default);
	UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
	if (retval != UA_STATUSCODE_GOOD)
	{
		UA_Client_delete(client);
		return (int)retval;
	}
	/*read the value attribute of the node.UA_Client_readValueAttribute is a wrapper for the
	raw read service available as UA_Client_Service_read.*/
	UA_Variant value;
	UA_Variant_init(&value);

	UA_NodeId testvar = UA_NODEID_STRING(1, "the.answer");
	retval = UA_Client_readValueAttribute(client, testvar, &value);

	if (retval == UA_STATUSCODE_GOOD) {
		UA_Int32 *p = (UA_Int32 *)value.data;
		printf("Var = %d \n", *p);
	}

	/*Clean up */
	UA_Variant_deleteMembers(&value);
	UA_Client_delete(client);
	return UA_STATUSCODE_GOOD;
}