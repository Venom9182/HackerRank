import React from 'react';
import Styles from './Styles.css'; 

function App() {
  return (
    <div className="App">
      <div className="container">
        <div className="row">
          <div className="col-md-6">
            <div className="logo-container">
              <img src="C:\Users\Acer\Downloads\logo f 1.png" alt="Standard Chartered Logo" className="img-fluid" />
            </div>
            <div className="welcome-message" style={{ color: 'white' }}>
              Welcome to the RW Tools
            </div>
          </div>
          <div className="col-md-6">
            <div className="login-container" style={{ backgroundColor: '#f2f2f2' }}>
              <h2 className="mb-4">Login</h2>
              <form action="#" method="post" style={{ textAlign: 'center' }}>
                <div className="form-group">
                  <label htmlFor="username">
                    <label htmlFor="username" style={{ fontFamily: 'com', sans-serif: '' }}></label>
                    <i className="icon fas fa-user"></i>
                    Username:
                  </label>
                  <input
                    type="number"
                    id="username"
                    name="username"
                    placeholder="Enter Username"
                    className="form-control"
                    min="0"
                    max="999999999"
                    onInput={(e) => (e.target.value = e.target.value.replace(/[^0-9]/g, ''))}
                    required
                  />
                </div>
                <div className="form-group">
                  <label htmlFor="password">
                    <i className="icon fas fa-lock"></i>
                    Password:
                  </label>
                  <div className="password-wrapper">
                    <input
                      type="password"
                      id="password"
                      name="password"
                      placeholder="Enter Password"
                      className="form-control"
                      required
                    />
                  </div>
                </div>
                <button type="submit" className="btn btn-primary" style={{ width: '200px', height: '40px' }}>
                  Login
                </button>
              </form>
              <div className="forgot-password mt-3">
                <a href="#">Forgot Password?</a>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}

export default App;
