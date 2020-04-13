select 'ORIGINAL -- NO INDEXES';

explain analyze
select *
from r
where s_id in (
    select s_id
    from s
    where s_20 = 0
    and t_id in (
        select t_id
        from t
        where t_5 = 0
    )
);

create index on r(s_id);
analyze r;
create index on s(t_id, s_20);
analyze s;
create index on t(t_5);
analyze t;

select 'ADD INDEX ON r(s_id),s(t_id, s_20), t(t_5)';

explain analyze
select *
from r
where s_id in (
    select s_id
    from s
    where s_20 = 0
    and t_id in (
        select t_id
        from t
        where t_5 = 0
    )
);

drop index r_s_id_idx, t_t_5_idx, s_t_id_s_20_idx;
