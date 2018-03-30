import numpy as np
import pitensor

def main():
    result = []
    for N in range(10, 200, 10):
        sites = pitensor.SpinHalf(N);
        psi = pitensor.MPS(sites)
        ampo = pitensor.AutoMPO(sites)
        for j in range(1, N):
            hz = pitensor.HTerm(1.0, [pitensor.SiteTerm("Sz", j), pitensor.SiteTerm("Sz", j+1)])
            hp = pitensor.HTerm(0.5, [pitensor.SiteTerm("S+", j), pitensor.SiteTerm("S-", j+1)])
            hm = pitensor.HTerm(0.5, [pitensor.SiteTerm("S-", j), pitensor.SiteTerm("S+", j+1)])

            ampo.add(hz)
            ampo.add(hp)
            ampo.add(hm)

        H = pitensor.toMPO(ampo)

        sweeps = pitensor.Sweeps(5);
        sweeps.maxm = [10, 40, 100, 200, 200]
        sweeps.cutoff = 1E-8

        energy = pitensor.dmrg(psi, H, sweeps, pitensor.Args(Quiet=True))
        result.append((N, energy/N))
        print("Ground state energy per site = {:.18f}".format(energy / N))
    result = np.array(result)
    np.savetxt('GroundStateEnergy.txt', result)

if __name__=='__main__':
    main()
