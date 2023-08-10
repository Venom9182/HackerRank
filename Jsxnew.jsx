import React, { useState } from 'react';
import './Styles.css'; // Import your CSS file
import logoImg from './logo f 1.png';

const Login = (props) => {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [isUpperCase, setIsUpperCase] = useState(false);
  const [isKeyboardOpen, setIsKeyboardOpen] = useState(false);

  const handleKeyPress = (key) => {
    if (key === 'clear') {
      setUsername('');
      setPassword('');
    } else if (key === 'backspace') {
      setUsername(username.slice(0, -1));
      setPassword(password.slice(0, -1));
    } else if (key === 'upperCase') {
      setIsUpperCase(!isUpperCase);
    } else if (key === 'space') {
      setUsername(username + ' ');
    } else if (key === 'close') {
      setIsKeyboardOpen(false);
    } else {
      const typedKey = isUpperCase ? key.toUpperCase() : key;
      if (document.activeElement.id === 'username') {
        setUsername(username + typedKey);
      } else if (document.activeElement.id === 'password') {
        setPassword(password + typedKey);
      }
    }
  };

  const keyboardLayout = [
    ['1', '2', '3', '4', '5', '6', '7', '8', '9', '0'],
    ['q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'],
    ['a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'backspace'],
    ['upperCase', 'z', 'x', 'c', 'v', 'b', 'n', 'm', 'clear', 'space'],
    ['close'],
  ];

  return (
    <div className="App">
      <div className="container">
        <div className="row">
          <div className="col-md-2">
            <div className="logo-container">
              <img src={logoImg} alt="Standard Chartered Logo" className="img-fluid" />
            </div>
            <div className="welcome-message" style={{ color: 'white', float: 'left' }}>
              Welcome to the RW Tools
            </div>
          </div>
          <div className="col-md-6">
            <div className="login-container" style={{ backgroundColor: '#f2f2f2', float: 'right', float: 'top' }}>
              <h2 className="mb-4">Login</h2>
              <form action="#" method="post" style={{ textAlign: 'center' }}>
                <div className="form-group">
                  <label htmlFor="username">
                    <i className="icon fas fa-user"></i>
                    Username:
                  </label>
                  <input
                    type="text"
                    id="username"
                    name="username"
                    placeholder="Enter Username"
                    className="form-control"
                    value={username}
                    onChange={(e) => setUsername(e.target.value)}
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
                      placeholder="🔐   Enter Password"
                      className="form-control"
                      value={password}
                      onChange={(e) => setPassword(e.target.value)}
                      required
                    />
                  </div>
                </div>
                <button
                  type="button"
                  className="btn btn-primary"
                  style={{ width: '200px', height: '40px', backgroundColor: '#007bff', borderRadius: '7px' }}
                  onClick={() => setIsKeyboardOpen(!isKeyboardOpen)}
                >
                  Open Virtual Keyboard
                </button>
                <div className="forgot-password mt-4" style={{ marginTop: '10px' }}>
                  <a href="#">Forgot Password?</a>
                </div>
              </form>
            </div>
          </div>
          {isKeyboardOpen && (
            <div className="col-md-4 virtual-keyboard-container">
              <div className="virtual-keyboard">
                {keyboardLayout.map((row, rowIndex) => (
                  <div key={rowIndex} className="keyboard-row">
                    {row.map((key, keyIndex) => (
                      <button
                        key={keyIndex}
                        className="keyboard-key"
                        onClick={() => handleKeyPress(key)}
                      >
                        {key === 'upperCase' ? (isUpperCase ? 'abc' : 'ABC') : key}
                      </button>
                    ))}
                  </div>
                ))}
              </div>
              <button
                className="close-keyboard-btn"
                onClick={() => setIsKeyboardOpen(false)}
              >
                Close Keyboard
              </button>
            </div>
          )}
        </div>
      </div>
    </div>
  );
};

export default Login;
