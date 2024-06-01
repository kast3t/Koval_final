#include "DB.h"

DB::DB() {
    int openResult = sqlite3_open16(L"db.sqlite3", &db);
    if (openResult != SQLITE_OK) {
        errMsg = (char*)sqlite3_errmsg(db);
        throw "Ошибка открытия БД";
    }

    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS clusters (cluster_number INTEGER, cluster_type TEXT, hex_data TEXT)";
    int execResult = sqlite3_exec(db, createTableSQL, NULL, NULL, &errMsg);
    if (execResult != SQLITE_OK) {
        throw "Ошибка создания таблицы";
    }

    int prepareResult = sqlite3_prepare_v2(db, "INSERT INTO clusters VALUES (?1, ?2, ?3)", -1, &pInsertStmt, NULL);
    if (prepareResult != SQLITE_OK) {
        errMsg = (char*)sqlite3_errmsg(db);
        throw "Ошибка подготовки запроса";
    }
}

DB::~DB() {
	sqlite3_finalize(pInsertStmt);
	sqlite3_close(db);
	delete errMsg;
}

void DB::insertData(unsigned int cluster_number, const char* cluster_type, const char* data) {
    sqlite3_bind_int64(pInsertStmt, 1, cluster_number);
    sqlite3_bind_text(pInsertStmt, 2, cluster_type, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(pInsertStmt, 3, data, -1, SQLITE_TRANSIENT);
    sqlite3_step(pInsertStmt);
    sqlite3_reset(pInsertStmt);
}

const char* DB::getErrMsg() {
    return errMsg;
}
