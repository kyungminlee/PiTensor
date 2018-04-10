import argparse
import json
import pitensor

def main():
    parser = argparse.ArgumentParser("exthubbard")
    parser.add_argument("inputjsonfile", type=argparse.FileType('r'))
    args = parser.parse_args()

    inputjson = json.load(args.inputjsonfile)

    N = inputjson['N']
    Npart = inputjson['Npart']
    sweepjson = inputjson['sweeps']
    sweeps = pitensor.Sweeps(len(sweepjson))
    sweeps.maxm = [s['maxm'] for s in sweepjson]
    sweeps.minm = [s['minm'] for s in sweepjson]
    sweeps.cutoff = [s['cutoff'] for s in sweepjson]
    sweeps.niter = [s['niter'] for s in sweepjson]
    sweeps.noise = [s['noise'] for s in sweepjson]

    t1 = inputjson['t1']
    t2 = inputjson['t2']
    U  = inputjson['U']
    V1 = inputjson['V1']
    quiet = inputjson['quiet']

    print(sweeps)

    sites = pitensor.Hubbard(N)
    ampo = pitensor.AutoMPO(sites)
    for i in range(1, N+1):
        ampo += (U, "Nupdn", i)
    for i in range(1, N):
        ampo += (-t1, "Cdagup", i, "Cup", i+1)
        ampo += (-t1, "Cdagup", i+1, "Cup", i)
        ampo += (-t1, "Cdagdn", i, "Cdn", i+1)
        ampo += (-t1, "Cdagdn", i+1, "Cdn", i)
        ampo += (V1, "Ntot", i, "Ntot", i+1)
    for i in range(1, N-1):
        ampo += (-t2, "Cdagup", i, "Cup", i+1)
        ampo += (-t2, "Cdagup", i+2, "Cup", i)
    H = ampo.toIQMPO()

    state = pitensor.InitState(sites)
    p = Npart
    for i in range(N, 0, -1):
        if p > i:
            print("Doubly occupying site {}".format(i))
            state.set(i, "UpDn")
            p -= 2
        elif p > 0:
            print("Singly occupying site ".format(i))
            state.set(i, "Up" if i % 2 == 1 else "Dn")
            p -= 1
        else:
            state.set(i, "Emp")

    psi = pitensor.IQMPS(state)
    print("Total QN = {}".format(pitensor.totalQN(psi)))

    energy = pitensor.dmrg(psi, H, sweeps, pitensor.Args(Quiet=quiet))

    print("Ground State energy = {}".format(energy))




if __name__=='__main__':
    main()