import uproot
import numpy as np
import matplotlib.pyplot as plt

# =========================
# configuration
# =========================
filename = "test.root"     # change to your file
tree_name = "DAMSA"
gamma_energy = 1000.0         # MeV

# =========================
# read ROOT file
# =========================
file = uproot.open(filename)
tree = file[tree_name]

edep_absorber = tree["edep_absorber"].array(library="np")
edep_ecal     = tree["edep_ECal"].array(library="np")
edep_leakage  = tree["edep_leakage"].array(library="np")

# sum energy
edep_sum = edep_absorber + edep_ecal + edep_leakage

print("Events:", len(edep_absorber))
print("Mean absorber :", np.mean(edep_absorber))
print("Mean ECal     :", np.mean(edep_ecal))
print("Mean leakage  :", np.mean(edep_leakage))
print("Mean total    :", np.mean(edep_sum))

# =========================
# plotting
# =========================
bins = 100

plt.figure()
plt.hist(edep_absorber, bins=bins)
plt.xlabel("Energy deposition in absorber (MeV)")
plt.ylabel("Events")
plt.yscale("log")
plt.title("Absorber Energy Deposition")
plt.savefig("edep_absorber.png")

plt.figure()
plt.hist(edep_ecal, bins=bins)
plt.xlabel("Energy deposition in ECal (MeV)")
plt.ylabel("Events")
plt.yscale("log")
plt.title("ECal Energy Deposition")
plt.savefig("edep_ecal.png")

plt.figure()
plt.hist(edep_leakage, bins=bins)
plt.xlabel("Leakage energy (MeV)")
plt.ylabel("Events")
plt.yscale("log")
plt.title("Leakage Energy")
plt.savefig("edep_leakage.png")

plt.figure()
plt.hist(edep_sum, bins=bins)
plt.axvline(gamma_energy, linestyle="--", label="500 MeV gamma")
plt.xlabel("Total energy (MeV)")
plt.ylabel("Events")
plt.title("Total Deposited Energy")
plt.yscale("log")
plt.legend()
plt.savefig("edep_sum.png")

plt.show()
