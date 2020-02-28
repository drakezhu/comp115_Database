select name from member except select name from member,routing where member_id = from_member_id and from_member_id = to_member_id order by name;

select birth_date from member where name = 'Tweetii';

select distinct message_date from message, (select * from member,routing where name = 'Zyrianyhippy' and member_id = from_member_id) subquery where message.message_id = subquery.message_id order by message.message_date desc;

select name from message, (select birth_date, name, message_id from routing,member where member_id = to_member_id) subquery where message.message_id = subquery.message_id and date_part('month',message.message_date) = date_part('month',subquery.birth_date) and date_part('day',message.message_date) = date_part('day',subquery.birth_date) order by name;

select message_date from message, member, (select * from member,routing where name = 'Unguiferous' and member_id = from_member_id) as a where a.to_member_id = member.member_id and member.name = 'Froglet' and message.message_id = a.message_id order by message_date;

select distinct member.name from routing, message, member where message_date = '2016-05-17' and routing.message_id = message.message_id and member.member_id = routing.from_member_id order by member.name;

select distinct member.name from member, (select routing.to_member_id from member,routing where member.name = 'Cephalophore' and member.member_id = routing.from_member_id) as a where member.member_id = a.to_member_id order by member.name;

select distinct sender, name as receiver from member, (select distinct member.name as sender, routing.to_member_id from message,routing,member where message.message_date = '2016-05-17' and message.message_id = routing.message_id and routing.from_member_id = member.member_id) as a where member.member_id = a.to_member_id order by sender,receiver;

select name, count(a.to_member_id) as messages from member left outer join (select to_member_id, message_id from member,routing where member_id = from_member_id and from_member_id != to_member_id and name = 'Lucarne') as a on member_id = a.to_member_id where name != 'Lucarne' group by a.to_member_id, name order by messages desc;

select member.name, count(a.from_member_id) as messages from (select from_member_id from routing group by from_member_id,message_id order by from_member_id)as a, member where a.from_member_id = member.member_id  group by member.name, a.from_member_id having count(a.from_member_id) >= 20 order by messages;

select max(birth_date) as max_birth_date, min(birth_date) as min_birth_date from member;


select count(*) from (select member_id from member where name = 'Abderian') as a, routing where routing.to_member_id = a.member_id group by a.member_id;

select name, newest_date, oldest_date from (select routing.from_member_id, max(message_date) as newest_date, min(message_date) as oldest_date from message, routing where message.message_id = routing.message_id group by routing.from_member_id, routing.from_member_id) as a full outer join member on a.from_member_id = member.member_id order by name;

select distinct a.a_date as DATE from (select message.message_date as a_date from routing, member, message where member.name = 'Unguiferous' and routing.from_member_id = member.member_id and routing.message_id = message.message_id) as a, (select message.message_date as b_date from routing, member, message where member.name = 'Abderian' and routing.from_member_id = member.member_id and routing.message_id = message.message_id) as b where a.a_date = b.b_date order by a.a_date;

select name from member where birth_date is null order by name;


select distinct name from member full outer join routing on routing.from_member_id = member.member_id where from_member_id is null;


