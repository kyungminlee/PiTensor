import argparse
import json
import numpy as np
import pitensor

def main():
    parser = argparse.ArgumentParser("dmrg_table")
    parser.add_argument("inputjsonfile", type=argparse.FileType('r'))
    args = parser.parse_args()

    inputjson = json.load(args.inputjsonfile)
    N = inputjson['N']

    sweepjson = inputjson['sweeps']
    sweeps = pitensor.Sweeps(len(sweepjson))
    sweeps.maxm = [s['maxm'] for s in sweepjson]
    sweeps.minm = [s['minm'] for s in sweepjson]
    sweeps.cutoff = [s['cutoff'] for s in sweepjson]
    sweeps.niter = [s['niter'] for s in sweepjson]
    sweeps.noise = [s['noise'] for s in sweepjson]

    quiet = inputjson['quiet']

    print(sweeps)

    sites = pitensor.SpinOne(N)
    ampo = pitensor.AutoMPO(sites)
    for j in range(1, N):
        ampo += (0.5, "S+", j, "S-", j+1)
        ampo += (0.5, "S-", j, "S+", j+1)
        ampo += ("Sz", j, "Sz", j+1)

    H = ampo.toMPO()

    state = pitensor.InitState(sites)

    for i in range(1, N):
        state.set(i, "Up" if i % 2 == 1 else "Dn")
    psi = pitensor.MPS(state)
    print("Initial energy = {}".format(pitensor.overlap(psi, H, psi)))

    energy = pitensor.dmrg(psi, H, sweeps, pitensor.Args(Quiet=quiet))

    print("Ground State energy = {}".format(energy))


if __name__=='__main__':
    main()