explain analyze
select t.*
from t
join s using (t_id)
join r using (s_id)
join u using (u_id)
where u_5 = 0;
