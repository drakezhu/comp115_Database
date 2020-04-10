create index on r(r_50p,s_id);
analyze r;
create index on s(s_4);
analyze s;

explain analyze
select r_10, s_20
from r
join s using (s_id)
where r_50p = 0
and s_4 = 0;

drop index s_s_4_idx, r_r_50p_s_id_idx;
