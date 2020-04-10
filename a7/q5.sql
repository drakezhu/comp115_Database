explain analyze
select r_10, s_20
from r
join s using (s_id)
where r_50p = 0
and s_4 = 0;
