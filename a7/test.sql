select 'ORIGINAL -- NO INDEXES';

explain
select *
from r
where r_10p between 1 and 2;

select 'ADD INDEX ON r_10P';

create index on r(r_10p);
analyze r;

explain
select *
from r
where r_10p between 1 and 2;

drop index r_r_10p_idx;
