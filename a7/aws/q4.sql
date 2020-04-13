select 'ORIGINAL -- NO INDEXES';

explain analyze
select t.*
from t
join s using (t_id)
join r using (s_id)
join u using (u_id)
where u_5 = 0;

select 'ADD INDEX ON r(s_id), s(u_id, t_id), u(u_5)';
create index on r(s_id);
analyze r;
create index on s(u_id, t_id);
analyze s;
create index on u(u_5);
analyze u;

explain analyze
select t.*
from t
join s using (t_id)
join r using (s_id)
join u using (u_id)
where u_5 = 0;

drop index u_u_5_idx, s_u_id_t_id_idx, r_s_id_idx;
