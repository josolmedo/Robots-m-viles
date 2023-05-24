
;************************************************
;*						*
;*	Initial state 				*
;*						*
;*                      J.Savage, UNAM          *
;*						*
;*                      1/5/20                  *
;*                                              *
;************************************************




(deffacts Initial-state-objects-rooms-zones-actors


; Objects definitions
	( item (type Objects) (name deposit)(room bedroom)(image table)( attributes no-pick brown)(pose 6.183334 7.000000 0.0))
	( item (type Objects) (name storage)(room livingroom)(image table)( attributes no-pick brown)(pose 3.183334 2.000000 0.0))
	( item (type Objects) (name Libro)(room studio)(zone deposit)(image blockA)(attributes pick)(pose 0.34 0.30 0.0))
	( item (type Objects) (name Martillo)(room livingroom)(zone storage)(image blockB)(attributes pick)(pose 0.9 1.4 0.0))
	( item (type Objects) (name Nino)(room bedroom)(zone deposit)(image blockC)(attributes no-pick)(pose 0.9 0.7 0.0))
	( item (type Objects) (name Mama)(room studio)(zone deposit)(image blockD)(attributes no-pick)(pose 0.3 0.5 0.0))
	;( item (type Objects) (name blockE)(room livingroom)(zone storage)(image blockE)(attributes pick)(pose 0.9 1.40 0.0))
	;( item (type Objects) (name blockF)(room livingoom)(zone storage)(image blockF)(attributes pick)(pose 0.9 1.60 0.0))
	;( item (type Objects) (name freespace)(room any)(zone any)(image none)(attributes none)(pose 0.0 0.0 0.0))

; Rooms definitions
	( Room (name livingroom)(zone storage)(zones dummy1 frontexit frontentrance storage dummy2)(center 0.50 0.80))
	( Room (name kitchen)(zone deposit)(zones dummy1 frontexit frontentrance deposit dummy2)(center 0.45 0.20))
	( Room (name bedroom)(zone deposit)(zones dummy1 frontexit frontentrance deposit dummy2)(center 0.4 0.10))
	( Room (name corridor)(zone deposit)(zones dummy1 frontexit frontentrance deposit dummy2)(center 0.4 0.10))
	( Room (name service)(zone deposit)(zones dummy1 frontexit frontentrance deposit dummy2)(center 0.4 0.10))
	( Room (name studio)(zone deposit)(zones dummy1 frontexit frontentrance deposit dummy2)(center 0.4 0.10))

; Robots definitions
	( item (type Robot) (name robot)(zone frontexit)(pose 1.048340 1.107002 0.0))

; Furniture definitions
	( item (type Furniture) (name cubestable)(zone bedroom)(image table)( attributes no-pick brown)(pose 6.183334 7.000000 0.0))

; Doors definitions
	( item (type Door) (name outsidedoor) (status closed) )

	( Arm (name left))

;stacks definitions
        ;(stack bedroom deposit blockA nil nil)
        ;(stack livingroom storage blockE blockD blockF)

        ;(real-stack bedroom deposit blockB blockA blockC)
        ;(real-stack livingroom storage blockE blockD blockF)


	;(goal-stack 1 livingroom storage nil nil blockA)
	;(goal-stack 2 livingroom storage blockB blockE blockC)
	(goal (room studio)(zone deposit)(move Martillo) (on Mama))
	(goal (room bedroom)(zone deposit)(move Libro) (on Nino))
	
        (plan (name cubes) (number 0)(duration 0))

)



