import subprocess
import matplotlib.pyplot as plt

def execute_executable(executable):
    """Execute the given executable and return its runtime."""
    start_time = time.time()
    subprocess.call(['./' + executable])
    end_time = time.time()
    return end_time - start_time

def generate_graph(runtimes):
    """Generate a graph of runtimes."""
    plt.bar(range(len(runtimes)), runtimes, align='center')
    plt.xlabel('Executable')
    plt.ylabel('Runtime (seconds)')
    plt.title('Runtimes of Executables')
    plt.xticks(range(len(runtimes)), ['Pthreads', 'Openmp'])
    plt.show()

if __name__ == "__main__":
    import time

    # Execute the executables and measure their runtimes
    runtimes = []
    for exe in ['p', 'omp']:
        runtime = execute_executable(exe)
        runtimes.append(runtime)

    # Generate and display the graph
    generate_graph(runtimes)
