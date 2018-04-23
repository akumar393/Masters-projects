require(gRbase)
require(Rgraphviz)

library(gRain)
library(gRim)
library(gRbase)
library(Rgraphviz)

packageVersion("gRim")
install.packages("gRbase")
install.packages("Rgraphviz")
source("http://bioconductor.org/biocLite.R")
biocLite(c("graph","RBGL","Rgraphviz"))

install.packages("gRain",ver)
install.packages("gRim")


d<-dag( ~smoke + bronc|smoke + dysp|bronc )
plot(d)

d<-dag( ~tub + either|tub+either|lung+lung|smoke + bronc|smoke )
plot(d)

y <- c("yes")
yn<-c("yes","no")
s <- parray("smoke", list(yn), c(.5, .5))

b.s <- parray(c("bronc","smoke"), list(y,yn), c(6,3))
l.s <- parray(c("lung","smoke"), list(y, yn), c(9,8))

s;b.s;l.s

a<- parray("asia", list(yn), c(.5, .5))
t.a <- parray(c("tub","asia"), list(y, yn), c(4,7))


joint <- tableMult( tableMult(s, b.s), tableMult(s,l.s)) ; ftable(joint)
joint<- tableMult( joint,t.a) ; ftable(joint)




dm <-moralize(d);
jtree<-ug(~tub:~smoke.bronc:smoke.lung);
par(mfrow=c(1,3)); plot(d); plot(dm); plot(jtree)

q1.sb <- tableMult(s, b.s); q1.sb
q2.sl <- tableMult(s, l.s); q2.sl

q3.ta<-tableMult(a, t.a) ;q3.ta

q1.b <- tableMargin(q1.sb, "bronc"); q1.b
q2.l <- tableMargin(q2.sl, "lung"); q2.l

plot(jtree)


q1.sb <- tableDiv(q1.sb, q1.b); q1.sb
q2.sl <- tableDiv(q2.sl, q2.l); q2.sl


q2.s <- tableMargin(q2.sl, "smoke"); q2.s

q1.sb <- tableMult(q1.sb, q2.s); q1.sb
q2.sl<- tableMult(q2.sl, q2.s); q2.sl

tableMargin(joint, c("tub","bronc"))

q2.sl

tableMargin(joint, c("tub","lung"))
tableMargin(joint, c("smoke","bronc"))
tableMargin(joint, c("smoke","lung"))


q1.joint<-tableMult(q1.sb, q3.ta); q1.joint    # joint of tub and bronc|smoke
q2.joint<-tableMult(q2.sl, q3.ta); q2.joint    # joint of tub and lung|smoke

q.joint<-tableMult(q1.joint, q2.joint); q.joint  # joint of q1 and q2

# Marginal Probabilites
tableMargin(q.joint, "bronc")
tableMargin(q.joint, "tub")
tableMargin(q.joint, "lung")



plot(jtree)


# With evidence asia="yes" and xray="yes"
d10<-dag( ~asia + tub|asia + either|tub+either|lung+lung|smoke + bronc|smoke +xray|either)
plot(d10)

y <- c("yes")
yn<-c("yes","no")
s <- parray("smoke", list(yn), c(.5, .5))
a<- parray("asia", list(yn), c(.5,.5))

b.s <- parray(c("bronc","smoke"), list(y,yn), c(6,3))
l.s <- parray(c("lung","smoke"), list(y, yn), c(9,8))
t.a <- parray(c("tub","asia"), list(y, yn), c(4,7))
#
t1.a<-parray(c("tub","asia"), list(yn, yn), c(4,1, 7,6))
l1.s <- parray(c("lung","smoke"), list(yn, yn), c(9,1, 2,8))

e.t1<-parray(c("either","tub1"), list(yn, yn), c(5,9, 3,6))
e.l1<-parray(c("either","lung1"), list(yn, yn), c(4,7, 3,8))

e<- parray("either", list(yn), c(.5, .5))

x.e<-parray(c("xray","either"), list(y, yn), c(4,9))


joint <- tableMult( tableMult(s, b.s), tableMult(s,l.s)) ; ftable(joint)
joint<- tableMult( joint,t.a) ; ftable(joint)
joint1<- tableMult( joint,x.e) ; ftable(joint1)


dm2 <-moralize(d10);
jtree2<-ug(~asia.tub:~smoke.bronc:smoke.lung:either.xray);
par(mfrow=c(1,3)); plot(d10); plot(dm2); plot(jtree2)


q4.ta <- tableMult(a, t.a); q4.ta
q4.t <- tableMargin(q4.ta, "tub"); q4.t
q4.ta <- tableDiv(q4.ta, q4.t); q4.t

q.e1<-tableMult(t1.a, e.t1); q.e
q.e2<-tableMult(l1.s, e.l1); q.e
q.e<-tableMult(q.e1,q.e2); q.e

q.t1 <- tableMargin(q.e, "tub"); q.t1
q.l1 <- tableMargin(q.e, "lung"); q.l1
q.e<-  tableDiv(q.e, q.l1)+ tableDiv(q.e, q.t1); q.e

length(q.e)

q5.xe <- tableMult(q.e, x.e); q5.xe
q5.e <- tableMargin(q5.xe, "either"); q5.e
q5.xe <- tableDiv(q5.xe, q5.e); q5.xe


#Joint Probability calculation
p.joint<-tableMult(q1.sb, q2.sl); p.joint
p.joint<-tableMult(p.joint, q4.ta); p.joint
p.joint<-tableMult(p.joint, q5.xe); p.joint



# Marginal Probabilites
tableMargin(p.joint, "bronc")
tableMargin(p.joint, "tub")
tableMargin(p.joint, "lung")



