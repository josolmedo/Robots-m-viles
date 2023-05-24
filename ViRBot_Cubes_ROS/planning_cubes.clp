;********************************************************
;*                                                      *
;*      planning_cubes.clp                              *
;*                                                      *
;*                                                      *
;*                      University of Mexico            *
;*                      Jesus Savage-Carmona            *                                      
;*                                                      *
;*                      6/22                            *
;*                                                      *
;********************************************************


(defglobal ?*plan_time* = 30000)

(defrule start
	?f <- (start action-planning)
        =>
        (retract ?f)
        (printout t "ROS Starting action planner ROS")
	(assert (action-planner active))
)


(defrule move-directly
	(action-planner active)
        ?goal <- (goal (move ?block1)(room ?room)(zone ?zone)(on ?block2&:(neq ?block2 freespace)))
        (plan (name ?name) (number ?num))
        (not (plan (name ?name) (number ?num1&:( > ?num1 ?num))))
	?f1 <- (item (type Objects) (name ?block1)(room ?room1)(zone ?zone1))
        =>
        (retract ?goal ?f1)
        (printout t ?block1 " will be moved onto free space in room " ?room1 crlf)

        (assert (plan (name ?name) (number (+ 1 ?num))(actions goto ?room1 ?zone1)(duration ?*plan_time*)) )
        (assert (plan (name ?name) (number (+ 2 ?num))(actions find-object ?block1)(duration ?*plan_time*)) )
        (assert (plan (name ?name) (number (+ 3 ?num))(actions mv ?block1 )(duration ?*plan_time*)) )
        (assert (plan (name ?name) (number (+ 4 ?num))(actions grab ?block1 )(duration ?*plan_time*)) )
        (assert (plan (name ?name) (number (+ 5 ?num))(actions goto ?room ?zone)(duration ?*plan_time*)) )
        (assert (plan (name ?name) (number (+ 6 ?num))(actions find-object ?block2)(duration ?*plan_time*)) )
        (assert (plan (name ?name) (number (+ 7 ?num))(actions go ?block2 )(duration ?*plan_time*)) )
        (assert (plan (name ?name) (number (+ 8 ?num))(actions drop ?block1 )(duration ?*plan_time*)) )
        (assert (attempt (move ?block1)(room ?room)(zone ?zone)(on ?block2)(number (+ 8 ?num) )))
)

(defrule finish-plan
	(declare (salience -10000))
        (plan (name ?name) (number ?num&:(neq ?num 0)))
        (not (plan (name ?name) (number ?num1&:( > ?num1 ?num))))
        ?f <- (plan (name ?name) (number 0))
        =>
	(retract ?f)
	(assert (finish-planner ?name ?num))
)

(defrule accomplish-plan
	(declare (salience 100))
	(plan (name ?name) (number ?num) (status accomplished))
	?f <- (attempt (move ?block1) (on ?block2) (room ?deposit) (zone ?zone) (number ?num)(status ?status&:(neq ?status finished)))
	?f1 <- (item (type Objects) (name ?block1)) 
        =>
        (printout t ?block1 " was moved on " ?block2 "." crlf)
	(modify ?f (room ?deposit) (zone ?zone)(status finished))
	(modify ?f1 (room ?deposit) (zone ?zone))
)
