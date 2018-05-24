
#%%
import numpy as np
#Input array
X=np.array([[1, 0], [0, 1], [1, 1], [0, 0]])

#Output
y=np.array([[1],[1],[0], [0]])

#Sigmoid Function
def sigmoid (x):
    return 1/(1 + np.exp(-x))

#Derivative of Sigmoid Function
def derivatives_sigmoid(x):
    return x * (1 - x)

#Variable initialization
epoch=10000 #Setting training iterations
lr=0.4 #Setting learning rate
inputlayer_neurons = X.shape[1] #number of features in data set
hiddenlayer_neurons = 3 #number of hidden layers neurons
output_neurons = 1 #number of neurons at output layer

#weight and bias initialization
wh=np.random.uniform(size=(inputlayer_neurons, hiddenlayer_neurons))
bh=np.random.uniform(size=(1, hiddenlayer_neurons))

wout=np.random.uniform(size=(hiddenlayer_neurons, output_neurons))
bout=np.random.uniform(size=(1, output_neurons))

for i in range(epoch):

    #Forward Propogation
    hidden_layer_input = np.dot(X, wh) + bh #Z1 - hidden layer # Z1 = X * W1 <----(1)
    hiddenlayer_activations = sigmoid(hidden_layer_input)   #A1 - activated hidden layer
    
    output_layer_input = np.dot(hiddenlayer_activations, wout) + bout #Z2 - output layer     # Z2 = A1 * W2 <----(2)
    output = sigmoid(output_layer_input) #A2 - activated output layer

    #Backpropagation
    E = y-output #dC/dA2
    
    slope_output_layer = derivatives_sigmoid(output) # dA2/dZ2 
    slope_hidden_layer = derivatives_sigmoid(hiddenlayer_activations) # dA1/dZ1
    
    d_output = E * slope_output_layer # dC/dA2 * dA2/dZ2 = dC/dZ2
    
    Error_at_hidden_layer = d_output.dot(wout.T) # dC/dZ2 * dZ2/dA1 = dC/dA1    # dC/dA1 = dZ2 * W2^T <---- (2)
    d_hiddenlayer = Error_at_hidden_layer * slope_hidden_layer # dC/dA1 * dA1/dZ1 = dC/dZ1
    
    wout += hiddenlayer_activations.T.dot(d_output) *lr # dC/dZ2 * dZ2/dW2 = dC/dW2    # dC/dW2 = A1^T * dC/dZ2 <----(2)
    bout += np.sum(d_output, axis=0, keepdims=True) *lr # b2 += dC/dZ2 * dZ2/db2(1) = dC/db2 
    
    wh += X.T.dot(d_hiddenlayer) *lr # dC/dZ1 * dZ1/dW1 = dC/dW1 # dW1 = X^T * dZ1 <----(1)
    bh += np.sum(d_hiddenlayer, axis=0, keepdims=True) *lr # b1 += dC/dZ1 * dZ1/db1(1) = dC/db1 

print(output)

result =  sigmoid(np.dot(sigmoid(np.dot([[1, 1]], wh) + bh), wout) + bout)
print("Result:", result)