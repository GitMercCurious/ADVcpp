import numpy as np
import matplotlib as mpl
from matplotlib import pyplot as plt
import matplotlib.ticker as ticker
mpl.rcParams['pdf.fonttype'] = 42
mpl.rcParams['ps.fonttype'] = 42


y = []
x = list(np.linspace(1, 30, 30))

with open("data.txt") as data:
    for time in data:
        y.append(int(time))

fig, ax = plt.subplots()

cores_x = np.linspace(1, 4, 40)
threads_x = np.linspace(5, 8, 40)
indiff_x = np.linspace(9, 30, 220)


cores_y = np.polyval(np.polyfit(x[0:4]+[6], y[0:4]+[0.45 * 1e9], 2), cores_x)
threads_y = np.polyval(np.polyfit(x[4:8], y[4:8], 1), threads_x)
indiff_y = np.polyval(np.polyfit(x[8:30], y[8:30], 1), indiff_x)


ax.scatter(x, y, marker='s', c='b', alpha=0.5)
ax.plot(cores_x, cores_y, marker='', c='r', label='using all 4 cores')
ax.plot(threads_x, threads_y, marker='', c='purple', label='adding 4 threads (all 8 threads)')
ax.plot(indiff_x, indiff_y, marker='', c='g', label='indifferent situation')
ax.legend()

plt.xlabel(r'$n$, потоки', fontsize=15)
plt.ylabel(r'$T$, с', fontsize=15)

plt.xlim(0, 31)
plt.ylim(0, 2e9)

ax.minorticks_on()
ax.grid(which='major',
        axis='both',
        )
ax.grid(which='minor',
        axis='both',
        linestyle=':'
        )

fig.set_figheight(7)
fig.set_figwidth(10)
fig.savefig("graph.png")
