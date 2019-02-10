import numpy as np
import pitensor

def main():
    N = 100
    sites = pitensor.SpinOne(N)
    psi = pitensor.MPS(sites)
    ampo = pitensor.AutoMPO(sites)
    for j in range(1, N):
        # Testing all three patterns of term addition to AutoMPO
        ampo += ("Sz", j, "Sz", j+1)
        ampo += (0.5, "S+", j, "S-", j+1)
        hm = pitensor.HTerm(0.5, [pitensor.SiteTerm("S-", j), pitensor.SiteTerm("S+", j+1)])
        ampo.add(hm)

    H = pitensor.toMPO(ampo)

    sweeps = pitensor.Sweeps(5);
    sweeps.maxm = [10, 40, 100, 200, 200]
    sweeps.cutoff = 1E-8

    #energy = pitensor.dmrg(psi, H, sweeps, pitensor.Args(Quiet=True))
    energy = pitensor.dmrg(psi, H, sweeps, pitensor.Args({'Quiet': True}))
    print("Ground state energy per site = {:.18f}".format(energy / N))

if __name__=='__main__':
    main()
