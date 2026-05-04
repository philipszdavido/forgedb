#  vm design


opcodes

projection 

Push cols
Project: loop through table and filter cols.


This maps directly to execution stages:

Scan → rows
Filter → WHERE
HashAggregate / SortAggregate → GROUP BY
Filter again → HAVING
Project → SELECT output


