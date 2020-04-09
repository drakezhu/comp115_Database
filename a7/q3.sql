create index on r(r_1p,r_10p);
analyze r;
create index on r(r_1p);
analyze r;
create index on r(r_10p);
analyze r;
create index on r(r_50p);
analyze r;
create index on r(r_1p,r_50p);
analyze r;
create index on r(r_10p,r_1p);
analyze r;
create index on r(r_50p,r_1p);
analyze r;
create index on r(r_50p,r_10p);
analyze r;
create index on r(r_10p,r_50p);
analyze r;
create index on r(r_1p,r_10p,r_50p);
analyze r;
create index on r(r_1p,r_50p,r_10p);
analyze r;
create index on r(r_10p,r_1p,r_50p);
analyze r;
create index on r(r_10p,r_50p,r_1p);
analyze r;
create index on r(r_50p,r_10p,r_1p);
analyze r;
create index on r(r_50p,r_1p,r_10p);
analyze r;


explain analyze
select * from r 
where r_1p between 0 and 5
and r_10p = 0
and r_50p = 0;

drop index r_r_1p_r_10p_idx, r_r_1p_idx,r_r_10p_idx,r_r_1p_r_10p_r_50p_idx;
