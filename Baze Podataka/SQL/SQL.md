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
| **DATETIME(fsp)**  | `DATE + TIME` formats                          |
Example of a table creation:
```sql
CREATE TABLE zaposljeni(
  id NUMBER(10) PRIMARY KEY,
  ime VARCHAR2(50) NOT NULL,
  prezime VARCHAR2(50) NOT NULL,
  plata NUMBER(10) NOT NULL,
  pol CHAR(1) NOT NULL,
  zaposljen DATE,
);
```

Creating a table with a composite key
```sql
CREATE TABLE proizvod_kategorija (
    pib     INT,
    id_kat  INT,
    some_data TEXT,
    PRIMARY KEY (pib, id_kat)
);
```

INSERT INTO %(%,...), inserts new entities into a table % and inserts into % columns
VALUES(%,...), defines which values to insert from an insert into statement
Example:
```sql
INSERT INTO zaposljeni(id, ime, prezime, plata, pol, zaposljen)
VALUES (1, 'Lazar', 'Lazarevic', 900000, 'M', TO_DATE('2025-03-08','YYYY-MM-DD'))
INSERT INTO zaposljeni(id, ime, prezime, plata, pol, zaposljen)
VALUES (2, 'Jovan', 'Jovanovic', 800000, 'M', TO_DATE('2025-03-08','YYYY-MM-DD'))
INSERT INTO zaposljeni(id, ime, prezime, plata, pol, zaposljen)
VALUES (3, 'Mila', 'Milosavljevic', 700000, 'Z', TO_DATE('2025-03-08','YYYY-MM-DD'));
```

## **Queries**:
| **Keyword** | **Description**                                |
|-------------|------------------------------------------------|
| **SELECT %** | Chooses columns to query from                |
| **DISTINCT** | Put after select to show only unique data                |
| **FROM %**   | Chooses the table from which to query columns defined in `SELECT` |
| **AS**       | Renames a column temporarily                 |

| **Operator** | **Description**                                    |
|--------------|----------------------------------------------------|
| **`\|\|`**     | Joins fields and columns together as strings      |
| **`*`**      | Wildcard that selects everything available   |
| **`;`**      | Denotes the end of the query                     |

Examples:
```sql
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
```sql
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
```sql
SELECT ime, prezime, plata
FROM zaposljeni
WHERE plata >= 50000

SELECT pol, AVG(plata)
FROM zaposljeni
GROUP BY pol
HAVING AVG(plata) < 100000
```

**Keywords**:
| **Keyword** | **Description**                                                       |
|-------------|-----------------------------------------------------------------------|
| **AND**     | Shows only where both conditions are true                             |
| **OR**      | Shows where either condition is true                                  |
| **LIKE %**  | Searches for a specific pattern (regular expression)                  |
| **IN()**    | Checks if a value exists in a set. Example: `WHERE id IN (1,3,5,7)`   |
| **NOT**     | Negates parameters. Example: `WHERE id NOT IN (2,4,6,8)`              |
| **BETWEEN % AND %** | Creates a range. Example: `* >= % AND % <= *`                 |
| **IS**      | Checks for set parameters like `NULL` or `NOT NULL`                   |

For string matching with LIKE you need wildcards,
| **Wildcard** | **Description**                    |
|--------------|------------------------------------|
| **%**        | Any characters or none            |
| **_**        | Any single character              |

Example:
```sql
SELECT ime, prezime, plata
FROM zaposljeni
WHERE plata >= 30000 AND ime LIKE '_____' AND prezime LIKE 'L%';

SELECT ime, prezime, id, plata
FROM zaposljeni
WHERE plata BETWEEN 30000 AND 500000 OR id IN(1,2,5,8,10) AND date IS NOT NULL;

SELECT pol, AVG(plata)
FROM zaposljeni
GROUP BY pol
HAVING AVG(plata) BETWEEN 30000 AND 500000;
```

## **Sorting**:
| **Keyword** | **Description**                                 |
|-------------|-------------------------------------------------|
| **ORDER BY %,%** | Sorts by the specified columns in the specified order |
| **ASC**         | Sorts in ascending order (default)          |
| **DESC**        | Sorts in descending order                   |

Example:
```sql
SELECT ime, prezime, id, plata
FROM zaposljeni
WHERE plata BETWEEN 30000 AND 500000 OR id IN(1,2,5,8,10) AND date IS NOT NULL;
ORDER BY plata DESC
```

## **Joining**:
| **Keyword** | **Description**                                 |
|-------------|-------------------------------------------------|
| **JOIN** | If not declared otherwise, is an inner join, returns fields that match in both tables (no nulls), usually primary to foreign key. |
| **USING**| Specifies that we are joining the same named columns |
| **ON**   | Sets the condition for joining the tables |

**PROIZVODJACI(pib, mat_br, naz, adresa)
KATEGORIJE(id_kat, naz, opis)
MODELI(id_mod, ozn, jac_m, br_vr, tip_gor, [pib, id_kat])**

```sql
SELECT knjige.naz AS "Naziv Knjiga", izdavaci.naz AS "Naziv Izdavaca"
FROM IZDAVACI JOIN KNJIGE ON (izdavaci.idizd = knjige.idizd)
-- returns all books with a set publisher
WHERE izdavaci.naz == 'CET'
-- only with publisher CET
ORDER BY knjige.naz;
```

```sql
SELECT DISTINCT proizvodj.naz
FROM MODELI JOIN PROIZVODJ ON (modeli.pib = proizvodj.pib)
WHERE tip_gor = 'dizel'
ORDER BY proizvodj.naz;
-- finds all manifacturers that have diesel powered cars
-- uses distinct to only show the name of manifacturers once
-- instead of it repeating for each instance of their car being diesel
```

```sql
SELECT ozn
FROM MODELI JOIN PROIZVODJACI ON (modeli.pib = proizvodjaci.pib)
            JOIN KATEGORIJE ON (modeli.id_kat = kategorija.id_kat)
WHERE proizvodjaci.naz = 'Mercedes_Benz' AND kategorije.naz = 'limuzina';
```
