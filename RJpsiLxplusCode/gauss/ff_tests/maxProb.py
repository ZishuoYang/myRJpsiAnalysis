f = open('psi2s_kiselev_probs.txt', 'r')
data = f.readlines()
maxprob = 0
for line in data:
    prob = float(line)
    print prob, " - ", maxprob
    if (prob > maxprob):
        maxprob = prob
print maxprob




