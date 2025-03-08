# SQL keywords and examples

## **Creation**:
CREATE TABLE %, creates a new table by name of %.
the structure is:
`column_name data_type constrains`
| **Data Type**      | **Description**                                  |
|--------------------|--------------------------------------------------|
| **CHAR(%)**        | Fixed-size string                              |
| **VARCHAR(%)**     | Variable-size string, ANSI standard            |
| **VARCHAR2(%)**    | Oracle standard for variable-size strings      |
| **INTEGER(%)**     | 32-bit integer                                 |
| **DATE**           | Format `YYYY-MM-DD`                            |
| **TIME**           | Format `00:00:00`                              |
| **DATETIME(fsp)**  | `DATE + TIME` formats

Example of a table creation:
```SQL
CREATE TABLE zaposljeni(
  id NUMBER(10) PRIMARY KEY,
  ime VARCHAR2(50) NOT NULL,
  prezime VARCHAR2(50) NOT NULL,
  plata NUMBER(10) NOT NULL,
  pol CHAR(1) NOT NULL,
  zaposljen DATE,
);

INSERT INTO %(%,...), inserts new entities into a table % and inserts into % columns
VALUES(%,...), defines which values to insert from an insert into statement
example:
INSERT INTO zaposljeni(id, ime, prezime, plata, pol, zaposljen)
VALUES (1, 'Lazar', 'Lazarevic', 900000, 'M', TO_DATE('08-03-2025','YYYY-MM-DD'))
INSERT INTO zaposljeni(id, ime, prezime, plata, pol, zaposljen)
VALUES (2, 'Jovan', 'Jovanovic', 800000, 'M', TO_DATE('08-03-2025','YYYY-MM-DD'))
INSERT INTO zaposljeni(id, ime, prezime, plata, pol, zaposljen)
VALUES (3, 'Mila', 'Milosavljevic', 700000, 'Z', TO_DATE('08-03-2025','YYYY-MM-DD'));
```

## **Queries**:
| **Keyword** | **Description**                                |
|-------------|------------------------------------------------|
| **SELECT %** | Chooses columns to query from                |
| **FROM %**   | Chooses the table from which to query columns defined in `SELECT` |
| **AS**       | Renames a column temporarily                 |

| **Operator** | **Description**                                    |
|--------------|----------------------------------------------------|
| **`\|\|`**     | Joins fields and columns together as strings      |
| **`*`**      | Wildcard that selects everything available   |
| **`;`**      | Denotes the end of the query                     |

Examples:
```SQL
SELECT ime,prezime,pol
FROM zaposljeni;

SELECT *
FROM zaposljeni;

SELECT ime || ' ' || prezime AS "Puno ime"
FROM zaposljeni;
-- this shows only 1 column names "Puno ime" with the format
-- of ime + ' ' + prezime
```

## **Grouping**:
When grouping you should use aggregates (otherwise its useless)
When using aggregates your table must be grouped by something
**GROUP BY %**, the table gets grouped by %
and if you have GROUP BY in your query then
in your SELECT part you can do any aggregate for a column

| **Aggregate** | **Description**           |
|--------------|---------------------------|
| **AVG()**    | Average value |
| **COUNT()**  | Number of rows|
| **MIN()**    | Minimum value |
| **MAX()**    | Maximum value |
| **SUM()**    | Sum of the values |

Example:
```SQL
SELECT SUM(plata), pol
FROM zaposljeni
GROUP BY pol
```

## **Filters**:
| **Filter**   | **Description**                                         |
|--------------|---------------------------------------------------------|
| **WHERE %**  | Filters the query columns by conditions specified in `%` |
| **HAVING %** | Filters the query aggregations by conditions specified in `%` |

# **Conditionals**:
Conditionals can consist of keywords or relational operators
or even both.

**Relational operators**:
| **Operator** | **Description**                |
|--------------|--------------------------------|
| **!=**       | Inequality                     |
| **=**        | Equal                           |
| **>**        | Greater than                   |
| **<**        | Less than                      |
| **>=**       | Greater than or equal          |
| **<=**       | Less than or equal             |

Examples:
```SQL
SELECT ime, prezime, plata
FROM zaposljeni
WHERE plata >= 50000

SELECT pol, AVG(plata)
FROM zaposljeni
HAVING AVG(plata) < 100000
```

**Keywords**:
| **Keyword** | **Description**                                                       |
|-------------|-----------------------------------------------------------------------|
| **AND**     | Shows only where both conditions are true                            |
| **OR**      | Shows where either condition is true                                 |
| **LIKE %**  | Searches for a specific pattern (regular expression)                 |
| **IN()**    | Checks if a value exists in a set. Example: `WHERE id IN (1,3,5,7)`   |
| **NOT**     | Negates parameters. Example: `WHERE id NOT IN (2,4,6,8)`              |
| **BETWEEN % AND %** | Creates a range. Example: `* >= % AND % <= *`                    |
| **IS**      | Checks for set parameters like `NULL` or `NOT NULL`                  |

For string matching with LIKE you need wildcards,
| **Wildcard** | **Description**                    |
|--------------|------------------------------------|
| **%**        | Any characters or none            |
| **_**        | Any single character              |

Example:
```SQL
SELECT ime, prezime, plata
FROM zaposljeni
WHERE plata >= 30000 AND ime LIKE '_____' AND prezime LIKE 'L%';

SELECT ime, prezime, id, plata
FROM zaposljeni
WHERE plata BETWEEN 30000 AND 500000 OR id IN(1,2,5,8,10) AND date IS NOT NULL;

SELECT pol, AVG(plata)
FROM zaposljeni
HAVING AVG(plata) BETWEEN 30000 AND 500000;
```

## **Sorting**:
| **Keyword** | **Description**                                 |
|-------------|-------------------------------------------------|
| **ORDER BY %,%** | Sorts by the specified columns in the specified order |
| **ASC**         | Sorts in ascending order (default)          |
| **DESC**        | Sorts in descending order                   |

Example:
```SQL
SELECT ime, prezime, id, plata
FROM zaposljeni
WHERE plata BETWEEN 30000 AND 500000 OR id IN(1,2,5,8,10) AND date IS NOT NULL;
ORDER BY plata DESC
```
