п»ї#pragma once
#include "sqlite3.h"
#include "Cluster.h"

class DB
{
private:
	sqlite3* db;
	sqlite3_stmt* pInsertStmt;
	char* errMsg = NULL;
public:
	DB();
	~DB();
	void insertData(unsigned int cluster_number, const char* cluster_type, const char* data);
	const char* getErrMsg();
};
