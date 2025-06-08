# SQL cheatsheet 2

## SQL knowledge

### Deletion

To delete a table is to drop a table  
you can either do:  
```sql
DROP TABLE % -- error if it doesnt exists
DROP TABLE IF EXISTS % -- catches exception
```

### Checking

To check a atribute at insert time you can do
```sql
CREATE TABLE table(
    atribute INT CHECK(atribute < 30)
);
```

## SQLITE specifics

To extract the create table schemes you do:  
```bash
sqlite3 PeerSpeak.db ".schema MREZE"
```

To see all your tables:
```sql
SELECT name FROM sqlite_master WHERE type='table';
```

Dates are considered as formatted strings.

## Oracle Apex specifics

To get a blob literal, you need to use HEXTORAW.
To get a date literal, TO_DATE(date, format) is used
