explain analyze
select * 
from r
where r_1p = 0
union
select *
from r
where r_10 = 0;
