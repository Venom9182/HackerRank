import React, { useEffect, useState } from 'react';
import './Login.css'; // Import your CSS file
import logoImg from './logo f 1.png';
import { Button } from 'bootstrap';
import ContactFormModal from './ContactFormModal';
import { useHistory } from 'react-router-dom';
import { Link } from 'react-router-dom';

const Login = (props) => {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [showVirtualKeyboard, setShowVirtualKeyboard] = useState(false);
  const [error, setError] = useState('');
  const [contactModalOpen, setContactModalOpen] = useState(false); 

  const storedUsername = 12345;
  const storedPassword = 12345;
  const storedAdminName = 54321;
  const storedAdminPassword = 54321;

  const history = useHistory();
    
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

  const handleSubmit = (e) => {
    e.preventDefault();
    
    if ((username ==storedUsername) && (password == storedPassword)) {
      setError(' ');
      console.log('Ops Login Successful');
      props.toggleLogin(true);
      props.toggleUser('opsUser')
      history.push('/userDashBoard/opsUser');
      
    }
    else if ((username ==storedAdminName) && (password == storedAdminPassword)) {
      setError(' ');
      console.log('Admin Successful');
      props.toggleLogin(true);
      props.toggleUser('adminUser')
      history.push('/userDashBoard/adminUser');
      
    }
    else {
      setError('⚠️ Incorrect Username or password. Please try again');
      console.log(username,password);
    }
  };

  const openContactModal = () => {
    setContactModalOpen(true);
  };

  const closeContactModal = () => {
    setContactModalOpen(false);
  };

  return (
    <div className="App1">
      <Link to="/Contact" className="contact-button" >
        Contact Us
      </Link>
      <div className="container">
        <div className="row">
          <div className="col-md-2">
            <div className="logo-container">
              <img src={logoImg} alt="Standard Chartered Logo" className="img-fluid" />
            </div>
            <div className="welcome-message" style={{ color: 'white', float: 'left' }}>
              Welcome to the Report Tools
            </div>
          </div>
          <div className="col-md-6">
            <div className="login-container" style={{ backgroundColor: '#f2f2f2' }}>
              <h2 className="mb-4">Login</h2>
              {error && <p className="error">{error}</p>}
              <form onSubmit={handleSubmit} style = {{textAlign: 'left'}}>
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
                    onInput = {(e) => (e.target.value = e.target.value.replace(/^[0-9]/g, ' '))}
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
                      value={password}
                      onChange={(e) => setPassword(e.target.value)}
                      required
                    />
                  </div>
                </div>
                <button type="submit" className="btn btn-primary" style={{ width: '200px', height: '40px', backgroundColor: '#007bff', borderRadius: '40px', marginLeft: '20px' }}>
                  Login
                </button>
                <button
                  className="btn btn-secondary"
                  style={{ marginLeft: '40px', borderRadius: '7px', marginTop: '8px',height: '35px' }}
                  onClick={() => setShowVirtualKeyboard(!showVirtualKeyboard)}
                >
                  Virtual Keyboard
                </button>
              </form>
              <div className="forgot-password mt-4" style={{ marginTop: '10px' }}>
                <a href="#">Forgot Password?</a>
              </div>
            </div>
          </div>
        </div>
      </div>
      {showVirtualKeyboard && (
        <div className="virtual-keyboard">
          {keyboardLayout.map((row, rowIndex) => (
            <div key={rowIndex} className="keyboard-row">
              {row.map((key, keyIndex) => (
                <button
                  key={keyIndex}
                  onClick={() => handleKeyPress(key)}
                  className="keyboard-key"
                >
                  {key}
                </button>
              ))}
            </div>
          ))}
        </div>
        
      )}
      <ContactFormModal isOpen={contactModalOpen} onClose={closeContactModal} />
    </div>
  );
}

export default Login;
