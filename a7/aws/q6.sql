select 'ORIGINAL -- NO INDEXES';

explain analyze
select * 
from r
where r_1p = 0
union
select *
from r
where r_10 = 0;

select 'ADD INDEX ON r(r_1p),r(r_10), r(r_1p, r_10)';
create index on r(r_1p);
create index on r(r_10);
create index on r(r_1p, r_10);
analyze r;

explain analyze
select * 
from r
where r_1p = 0
union
select *
from r
where r_10 = 0;

select 'SAME INDEX ON r(r_1p),r(r_10), r(r_1p, r_10)';
explain analyze
select * 
from r
where r_1p = 0 or r_10 = 0;
drop index r_r_1p_idx, r_r_10_idx, r_r_1p_r_10_idx;
