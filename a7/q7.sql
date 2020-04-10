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
