#  vm design


opcodes

projection 

Push cols
Project: loop through table and filter cols.


# SELECT

This maps directly to execution stages:

Scan → rows
Filter → WHERE
HashAggregate / SortAggregate → GROUP BY
Filter again → HAVING
Project → SELECT output


Execution order:

FROM
WHERE (filter rows)
GROUP BY (create groups)
HAVING (filter groups)
SELECT

SELECT [DISTINCT | ALL]
    select_list
FROM
    table_references
[JOIN ...]
WHERE
    row_filter_condition
GROUP BY
    grouping_columns
HAVING
    group_filter_condition
WINDOW
    window_definitions
ORDER BY
    sort_expressions
LIMIT
    number_of_rows
OFFSET
    number_of_rows;


1. FROM / JOIN
2. WHERE
3. GROUP BY
4. HAVING
5. SELECT (projection)
6. WINDOW (if used)
7. ORDER BY
8. LIMIT / OFFSET

The **full `SELECT` statement structure** in SQL can get quite rich, but there *is* a standard logical order that most databases follow internally when executing it.

---

# 🧱 Complete SQL `SELECT` structure

Here is the full canonical form:

```sql id="3n9k2a"
SELECT [DISTINCT | ALL]
    select_list
FROM
    table_references
[JOIN ...]
WHERE
    row_filter_condition
GROUP BY
    grouping_columns
HAVING
    group_filter_condition
WINDOW
    window_definitions
ORDER BY
    sort_expressions
LIMIT
    number_of_rows
OFFSET
    number_of_rows;
```

Not all parts are required — only `SELECT` and `FROM` are mandatory.

---

# 🧠 Execution order (VERY important)

Even though you *write* it top-down, SQL executes it like this:

```text
1. FROM / JOIN
2. WHERE
3. GROUP BY
4. HAVING
5. SELECT (projection)
6. WINDOW (if used)
7. ORDER BY
8. LIMIT / OFFSET
```

---

# 🔍 Breakdown of each part

## 1. `SELECT` (what you output)

```sql
SELECT name, age
```

Defines:

* columns
* expressions
* aggregates

---

## 2. `FROM` (data source)

```sql
FROM users
```

Can include:

* tables
* subqueries
* joins

---

## 3. `JOIN` (combine tables)

```sql
FROM users
JOIN orders ON users.id = orders.user_id
```

Types:

* INNER JOIN
* LEFT JOIN
* RIGHT JOIN
* FULL JOIN

---

## 4. `WHERE` (filter rows BEFORE grouping)

```sql
WHERE age > 18
```

* works on raw rows
* cannot use aggregates like `SUM`

---

## 5. `GROUP BY` (create groups)

```sql
GROUP BY country
```

Turns rows into grouped buckets.

---

## 6. `HAVING` (filter groups)

```sql
HAVING COUNT(*) > 5
```

* works AFTER grouping
* allows aggregates

---

## 7. `WINDOW` (advanced analytics)

```sql
OVER (PARTITION BY country ORDER BY date)
```

Used for:

* running totals
* rankings
* moving averages

---

## 8. `ORDER BY` (sorting output)

```sql
ORDER BY total_spent DESC
```

* sorts final result
* happens AFTER SELECT

---

## 9. `LIMIT / OFFSET` (pagination)

```sql
LIMIT 10 OFFSET 20
```

* LIMIT = how many rows
* OFFSET = skip rows

---

# 🧪 Full example

```sql id="0xq8vb"
SELECT
    customer,
    SUM(amount) AS total_spent
FROM orders
WHERE status = 'paid'
GROUP BY customer
HAVING SUM(amount) > 100
ORDER BY total_spent DESC
LIMIT 10;
```

---

# 🧠 Mental model (important)

Think of SQL as a pipeline:

```text
RAW TABLES
   ↓ FROM / JOIN
FILTER ROWS
   ↓ WHERE
GROUP ROWS
   ↓ GROUP BY
FILTER GROUPS
   ↓ HAVING
SHAPE OUTPUT
   ↓ SELECT
ANALYTICS (optional)
   ↓ WINDOW
SORT RESULTS
   ↓ ORDER BY
CUT RESULTS
   ↓ LIMIT
```

---

# ⚙️ If you're building a DB engine / VM

This maps directly to execution stages:

### Physical pipeline:

```text
Scan
 → Filter (WHERE)
 → Join
 → Aggregate (GROUP BY)
 → Filter (HAVING)
 → Project (SELECT)
 → Sort (ORDER BY)
 → Limit
```

---

# 🚀 Key insight

`SELECT` is NOT executed first — it is actually one of the *last logical steps*, even though it appears first in the query.

---

