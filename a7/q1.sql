select 'ORIGINAL -- NO INDEXES';



explain
select *
from r
where r_2 = 0;

select 'ADD INDEX ON r_2';

create index on r(r_2);
analyze r;

explain analyze
select *
from r
where r_2 = 0;

drop index r_r_2_idx;

select 'ORIGINAL -- NO INDEXES';

explain
select *
from r
where r_1p = 0;

select 'ADD INDEX ON r_1P';

create index on r(r_1p);
analyze r;

explain analyze
select *
from r
where r_1p = 0;

drop index r_r_1p_idx;

select 'ORIGINAL -- NO INDEXES';

explain
select *
from r
where r_50p = 0;

select 'ADD INDEX ON r_50P';

create index on r(r_50p);
analyze r;

explain analyze
select *
from r
where r_50p = 0;

drop index r_r_50p_idx;
