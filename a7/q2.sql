select 'ORIGINAL -- NO INDEXES';

explain
select *
from r
where r_1p = 0
and r_10p = 0
and r_50p = 0;

select 'ADD INDEX ON (r_50p,r_1p,r_10p)';
create index on r(r_50p,r_1p,r_10p);
analyze r;

explain
select *
from r
where r_1p = 0
and r_10p = 0
and r_50p = 0;

drop index r_r_50p_r_1p_r_10p_idx;
