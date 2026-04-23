#  ForgeDB

```sql
SELECT * FROM db

{
action: SELECT,
inputs: 
condition: COND,
database: db
}

create table table_name (
a type1,
b type2,
...
index (c, b, a),
index (d, e, f),
primary key (a, b),
);

select expr... from table_name conditions limit x, y;
insert into table_name (cols...) values (a, b, c)...;
delete from table_name conditions limit x, y;
update table_name set a = expr, b = expr, ... conditions limit x, y;
```
```
SELECT * FROM db
```

instructions:

push table
push *
get
pop
pop
