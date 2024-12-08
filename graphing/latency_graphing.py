import matplotlib.pyplot as plt



def main():

    py_latencys = ext_latencys("C:/Users/User/Documents/Results/robot_latency_tests/raw/latency_python.txt")
    cpp_latencys = ext_latencys("C:/Users/User/Documents/Results/robot_latency_tests/raw/latency_cpp.txt")

    plot_latencys(py_latencys, cpp_latencys)

    return


#Go through data and extract line by line
def ext_latencys(filename):

    latencys = []

    #Format is the same so its line
    with open(filename) as f:
        for line in f:
            latencys.append(line)

    return latencys

#Plot the latencies on the same graph against the number of iterations
def plot_latencys(py_lats, cpp_lats):

    x = len(py_lats)

    plt.plot(x, py_lats, color="r", label="Python")
    plt.plot(x, cpp_lats, color="g", label="Cpp")

    plt.xlabel("Iteration")
    plt.ylabel("Time")
    plt.title("ABB Ping latencys")

    plt.legend()

    plt.show()
    

    return




if __name__ == "__main__":
    print("Plotting")