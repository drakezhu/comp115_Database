# q0
select name from member except select name from member,routing where member_id = from_member_id and from_member_id = to_member_id order by name;
#     name     
#--------------
# Hindforemost
# Ijreilly
# Squeezewas
#(3 rows)

# q1
select birth_date from member where name = 'Tweetii';
# birth_date 
#------------
# 1989-10-01
#(1 row)


# q2
select distinct message_date from message, (select * from member,routing where name = 'Zyrianyhippy' and member_id = from_member_id) subquery where message.message_id = subquery.message_id order by message.message_date;
# message_date 
#--------------
# 2015-01-05
# 2015-04-16
# 2015-04-30
# 2015-06-25
# 2015-11-04
# 2015-11-15
# 2016-02-14
# 2016-08-05
# 2017-02-22
# 2017-02-23
# 2017-11-13
#(11 rows)

# q3
select name from message, (select birth_date, name, message_id from routing,member where member_id = to_member_id) subquery where message.message_id = subquery.message_id and date_part('month',message.message_date) = date_part('month',subquery.birth_date) and date_part('day',message.message_date) = date_part('day',subquery.birth_date) order by name;
#     name     
#--------------
# Cynosure
# Salpiglossis
# Unguiferous
#(3 rows)

# q4
select message_date from message, member, (select * from member,routing where name = 'Unguiferous' and member_id = from_member_id) as a where a.to_member_id = member.member_id and member.name = 'Froglet' and message.message_id = a.message_id order by message_date;
# message_date 
#--------------
# 2015-01-21
# 2016-07-09
#(2 rows)

# q5
select distinct member.name from routing, message, member where message_date = '2016-05-17' and routing.message_id = message.message_id and member.member_id = routing.from_member_id order by member.name;
#	name     
#-------------
# Abderian
# Oscitate
# Squeezewas
# Unguiferous
#(4 rows)

# q6
select distinct member.name from member, (select routing.to_member_id from member,routing where member.name = 'Cephalophore' and member.member_id = routing.from_member_id) as a where member.member_id = a.to_member_id order by member.name;
#     name     
#--------------
# Abderian
# Bamboozled
# Botuliform
# Cephalophore
# Cynosure
# Flyaway
# Froglet
# Intaglio
# Lucarne
# Moneyocracy
# Oscitate
# Salpiglossis
# Tweetii
# Unguiferous
# Zyrianyhippy
#(15 rows)

# q7
select distinct sender, name as receiver from member, (select distinct member.name as sender, routing.to_member_id from message,routing,member where message.message_date = '2016-05-17' and message.message_id = routing.message_id and routing.from_member_id = member.member_id) as a where member.member_id = a.to_member_id order by sender,receiver;
#	sender    |   receiver   
#-------------+--------------
# Abderian    | Abderian
# Abderian    | Cephalophore
# Abderian    | Cynosure
# Abderian    | Froglet
# Abderian    | Oscitate
# Oscitate    | Bamboozled
# Oscitate    | Flyaway
# Oscitate    | Hindforemost
# Oscitate    | Salpiglossis
# Squeezewas  | Anchusa
# Squeezewas  | Bamboozled
# Squeezewas  | Botuliform
# Squeezewas  | Moneyocracy
# Squeezewas  | Normalcy
# Unguiferous | Flyaway
# Unguiferous | Moneyocracy
# Unguiferous | Tweetii
# Unguiferous | Unguiferous
#(18 rows)

