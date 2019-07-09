// OPCServerTest.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <signal.h>
#include "open62541.h"

UA_Boolean runing = true;
static void stopHandler(int sig)
{
	UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl c");
	runing = false;
}

static void addVariable(UA_Server *server)
{
	/*Define the attribute of the myInteger variable node*/
	UA_VariableAttributes attr = UA_VariableAttributes_default;
	UA_Int32 myInteger = 43;
	UA_Variant_setScalar(&attr.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);
	attr.description = UA_LOCALIZEDTEXT("en-US", "the answer");
	attr.displayName = UA_LOCALIZEDTEXT("en-US", "the answer");
	attr.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
	attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

	/*Add the variable node to the information model*/
	UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "the.answer");
	UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, "the answer");
	UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
	UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
	UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId, \
		parentReferenceNodeId, myIntegerName, \
		UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), \
		attr, NULL, NULL);

}

static void addVariable1(UA_Server *server)
{
	/*Define the attribute of the myInteger variable node*/
	UA_VariableAttributes attr = UA_VariableAttributes_default;
	UA_Int32 myInteger = 433;
	UA_Variant_setScalar(&attr.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);
	attr.description = UA_LOCALIZEDTEXT("en-US", "the answer1");
	attr.displayName = UA_LOCALIZEDTEXT("en-US", "中文标题");
	attr.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
	attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

	/*Add the variable node to the information model*/
	UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "the.answer3");
	UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, "the answer4");
	UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
	UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
	UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId, \
		parentReferenceNodeId, myIntegerName, \
		UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), \
		attr, NULL, NULL);

}


int main(void)
{	
	signal(SIGINT, stopHandler);
	signal(SIGTERM, stopHandler);
	UA_ServerConfig *config = UA_ServerConfig_new_default();
	UA_Server *server = UA_Server_new(config);

	addVariable(server);
	addVariable1(server);

	UA_StatusCode retval = UA_Server_run(server, &runing);
	UA_Server_delete(server);
	UA_ServerConfig_delete(config);
	return (int)retval;

	/*signal(SIGINT, stopHandler);
	signal(SIGTERM, stopHandler);

	UA_ServerConfig *config = UA_ServerConfig_new_default();
	//UA_ServerNetworkLayer nl =
	//	UA_ServerNetworkLayerTCP(UA_ConnectionConfig_standard, 16664);
	//config->networkLayers = &nl;
	config->networkLayersSize = 1;
	UA_Server *server = UA_Server_new(config);

	UA_Server_run(server, &runing);
	UA_Server_delete(server);
	//nl.deleteMembers(&nl);
	return 0;*/
}

