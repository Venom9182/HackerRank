import React, { useState, useEffect } from 'react';
import './Styles.css'; // Import your CSS file
import logoImg from './logo f 1.png';

const Login = (props) => {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [keyboardVisible, setKeyboardVisible] = useState(false);
  const [keyboardPosition, setKeyboardPosition] = useState({ x: 0, y: 0 });

  const handleKeyPress = (key) => {
    if (key === 'clear') {
      setUsername('');
      setPassword('');
    } else if (key === 'backspace') {
      setUsername(username.slice(0, -1));
      setPassword(password.slice(0, -1));
    } else {
      setUsername(username + key);
      setPassword(password + key);
    }
  };

  const keyboardLayout = [
    ['1', '2', '3', '4', '5', '6', '7', '8', '9', '0'],
    ['q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'],
    ['a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'backspace'],
    ['z', 'x', 'c', 'v', 'b', 'n', 'm', 'clear'],
  ];

  const handleKeyboardButtonClick = (key) => {
    handleKeyPress(key);
  };

  const handleToggleKeyboard = () => {
    setKeyboardVisible(!keyboardVisible);
  };

  const handleMouseDown = (e) => {
    if (keyboardVisible) {
      const offsetX = e.clientX - keyboardPosition.x;
      const offsetY = e.clientY - keyboardPosition.y;
      setKeyboardPosition({ x: offsetX, y: offsetY });
    }
  };

  useEffect(() => {
    if (keyboardVisible) {
      document.addEventListener('mousemove', handleMouseDown);
      return () => {
        document.removeEventListener('mousemove', handleMouseDown);
      };
    }
  }, [keyboardVisible]);

  const handleSubmit = (e) => {
    e.preventDefault();
    // You can use the 'username' and 'password' states here for further processing
    console.log('Username:', username);
    console.log('Password:', password);
    // You can also perform API requests or other actions here
  };

  return (
    <div className="App">
      <div className="container">
        <div className="row">
          <div className="col-md-2">
            <div className="logo-container">
              <img src={logoImg}  alt="Standard Chartered Logo" className="img-fluid" />
            </div>
            <div className="welcome-message" style={{ color: 'white', float: 'left'}}>
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
                    type="number"
                    id="username"
                    name="username"
                    placeholder="Enter Username"
                    className="form-control"
                    min="0"
                    max="999999999"
                    value={username}
                    onChange = {(e) => setUsername(e.target.value)}
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
                      placeholder="🔐   Enter Password"
                      className="form-control"
                      value={password}
                      onChange = {(e) => setPassword(e.target.value)}
                      required
                    />
                  </div>
                </div>
                <button type="submit" className="btn btn-primary" style={{ width: '200px', height: '40px', backgroundColor : '#007bff', borderRadius : '7px'}}>
                  Login
                </button>
                <button type="button" className="btn btn-secondary ml-2" onClick={handleToggleKeyboard}>
                  Virtual Keyboard
                </button>
              </form>
              <div className="forgot-password mt-4" style={{ marginTop: '10px'}}>
                <a href="#">Forgot Password?</a>
              </div>
            </div>
          </div>
        </div>
      </div>
      {keyboardVisible && (
        <div
          className="virtual-keyboard"
          style={{
            position: 'absolute',
            left: keyboardPosition.x,
            top: keyboardPosition.y,
          }}
        >
          {keyboardLayout.map((row, rowIndex) => (
            <div key={rowIndex} className="keyboard-row">
              {row.map((key, keyIndex) => (
                <button
                  key={keyIndex}
                  className="keyboard-key"
                  onClick={() => handleKeyboardButtonClick(key)}
                >
                  {key === 'backspace' ? (
                    <i className="fas fa-backspace" />
                  ) : key === 'clear' ? (
                    <i className="fas fa-times" />
                  ) : (
                    key
                  )}
                </button>
              ))}
            </div>
          ))}
          <button className="keyboard-close" onClick={handleToggleKeyboard}>
            <i className="fas fa-times" />
          </button>
          <button className="keyboard-uppercase" onClick={() => console.log("Uppercase/Lowercase toggle")}>
            <i className="fas fa-sort" />
          </button>
        </div>
      )}
    </div>
  );
}

export default Login;
