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

# q8
select count(*) from (select to_member_id from routing,member where from_member_id != to_member_id and name = 'Lucarne' and member_id = from_member_id) as a;

# count 
#-------
#	39
#(1 row)

# q9

select a.from_member_id from (select from_member_id from routing group by from_member_id,message_id order by from_member_id) as a group by a.from_member_id having count(a.from_member_id) >= 20;

# from_member_id 
#----------------
#             18
#(1 row)

# q10

select max(birth_date) as max_birth_date, min(birth_date) as min_birth_date from member;
# max_birth_date | min_birth_date 
#----------------+----------------
# 2010-10-16     | 1950-12-25
#(1 row)

# q11
select count(*) from (select member_id from member where name = 'Abderian') as a, routing where routing.to_member_id = a.member_id group by a.member_id;

# count 
#-------
#	46
#(1 row)

# q12
select name, newest_date, oldest_date from (select routing.from_member_id, max(message_date) as newest_date, min(message_date) as oldest_date from message, routing where message.message_id = routing.message_id group by routing.from_member_id, routing.from_member_id) as a full outer join member on a.from_member_id = member.member_id order by name;
#     name     | newest_date | oldest_date 
#--------------+-------------+-------------
# Abderian     | 2017-11-07  | 2015-03-05
# Anchusa      | 2017-10-24  | 2015-04-01
# Bamboozled   | 2017-11-12  | 2015-01-22
# Botuliform   | 2017-11-04  | 2015-02-11
# Cephalophore | 2017-12-02  | 2015-06-19
# Cynosure     | 2017-12-23  | 2015-07-09
# Flyaway      | 2017-06-21  | 2015-02-17
# Froglet      | 2017-09-18  | 2016-11-07
# Hindforemost | 2017-11-12  | 2015-02-06
# Ijreilly     |             | 
# Intaglio     | 2017-12-14  | 2015-03-26
# Lucarne      | 2017-12-12  | 2015-05-13
# Moneyocracy  | 2017-10-11  | 2015-03-18
# Normalcy     | 2017-12-30  | 2015-03-19
# Oscitate     | 2017-11-07  | 2015-01-17
# Salpiglossis | 2017-11-05  | 2015-11-26
# Squeezewas   | 2017-12-30  | 2015-04-15
# Tweetii      | 2017-12-31  | 2015-04-03
# Unguiferous  | 2016-10-20  | 2015-01-05
# Zyrianyhippy | 2017-11-13  | 2015-01-05
#(20 rows)

# q13
select distinct a.a_date as DATE from (select message.message_date as a_date from routing, member, message where member.name = 'Unguiferous' and routing.from_member_id = member.member_id and routing.message_id = message.message_id) as a, (select message.message_date as b_date from routing, member, message where member.name = 'Abderian' and routing.from_member_id = member.member_id and routing.message_id = message.message_id) as b where a.a_date = b.b_date order by a.a_date;
#	date    
#------------
# 2016-05-17
# 2016-05-18
#(2 rows)

# q14
select name from member where birth_date is null order by name;
#	name   
#----------
# Flyaway
# Normalcy
#(2 rows)

# q15
select distinct name from member full outer join routing on routing.from_member_id = member.member_id where from_member_id is null;
#	name   
#----------
# Ijreilly
#(1 row)

