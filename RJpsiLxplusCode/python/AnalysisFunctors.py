def times(a,b):
    return "(" + a + ")*(" + b + ")"

def div(a,b):
    return "(" + a + ")/(" + b + ")"

def square(x):
    return times(x,x)

def squareroot(x):
    return "sqrt(" + x + ")"

# TWO BODY DECAY FUNCTORS

P1 = "CHILD(P,1)"
P1X = "CHILD(PX,1)"
P1Y = "CHILD(PY,1)"
P1Z = "CHILD(PZ,1)"

P2 = "CHILD(P,2)"
P2X = "CHILD(PX,2)"
P2Y = "CHILD(PY,2)"
P2Z = "CHILD(PZ,2)"

# CALCULATING PHID
# The magnet polarity cannot easily be accessed from Python
# I can get the most bang for my buck by calculating the dot product between the decay plane normal and the y axis
# Call this DecayPlaneTilt; then phiD = cos(Pol*DecayPlaneTilt)

NUM = times(P1Z,P2X) + "-" + times(P1X,P2Z)
DOT = times(P1X,P2X) + "+" + times(P1Y,P2Y) + "+" + times(P1Z,P2Z)
DENOM = squareroot(square(times(P1,P2)) + "-" + square(DOT))
DECAYPLANETILT = div(NUM,DENOM)

# CALCULATING MOMENTUM DIFFERENCE

MOMDIFF = P1 + "-" + P2

# CALCULATING ETA
