#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

/* Callback function to display the query results */
static int callback(void *data, int argc, char **argv, char **colName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", colName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;
    char *sql;
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create table */
    sql = "CREATE TABLE IF NOT EXISTS Users(" \
          "ID INT PRIMARY KEY NOT NULL," \
          "Name TEXT NOT NULL," \
          "Age INT NOT NULL);";
    
    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    /* Insert into table */
    sql = "INSERT INTO Users (ID, Name, Age) VALUES (1, 'Alice', 30);" \
          "INSERT INTO Users (ID, Name, Age) VALUES (2, 'Bob', 25);";

    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Records inserted successfully\n");
    }

    /* Select data */
    sql = "SELECT * FROM Users;";
    rc = sqlite3_exec(db, sql, callback, (void*)data, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }

    /* Update data */
    sql = "UPDATE Users SET Age = 31 WHERE ID = 1;";
    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Record updated successfully\n");
    }

    /* Delete data */
    sql = "DELETE FROM Users WHERE ID = 2;";
    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Record deleted successfully\n");
    }

    /* Close database */
    sqlite3_close(db);
    return 0;
}
