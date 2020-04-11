-- Store in the routing table the rows (from_member_id, to_member_id, x), 
-- for each message id x in message_ids.
-- The return value should be the number of rows inserted.

create or replace function store_routing(
    from_member_id int, 
    to_member_id int, 
    message_ids int[]) returns int as $$
declare
    mid int;
    insert_count int = 0;
begin
    -- IMPLEMENT ME
    return -1;
end
$$ language plpgsql;
