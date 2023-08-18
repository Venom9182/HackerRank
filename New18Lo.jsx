import React, { useState } from 'react';
import './Login.css'; // Import your CSS file
import logoImg from './logo f 1.png';
import ContactFormModal from './ContactFormModal'; // Import the contact modal component
import { useHistory } from 'react-router-dom';

const Login = (props) => {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [showVirtualKeyboard, setShowVirtualKeyboard] = useState(false);
  const [error, setError] = useState('');
  const [contactModalOpen, setContactModalOpen] = useState(false); // State for the contact modal

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

    if (username == storedUsername && password == storedPassword) {
      setError(' ');
      console.log('Ops Login Successful');
      props.toggleLogin(true);
      props.toggleUser('opsUser');
      history.push('/userDashBoard/opsUser');
    } else if (username == storedAdminName && password == storedAdminPassword) {
      setError(' ');
      console.log('Admin Successful');
      props.toggleLogin(true);
      props.toggleUser('adminUser');
      history.push('/userDashBoard/adminUser');
    } else {
      setError('⚠️ Incorrect Username or password. Please try again');
      console.log(username, password);
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
      <button className="contact-button" onClick={openContactModal}>
        Contact Us
      </button>
      <div className="container">
        <div className="row">
          <div className="col-md-2">
            {/* ... rest of the code ... */}
          </div>
          <div className="col-md-6">
            {/* ... rest of the code ... */}
          </div>
        </div>
      </div>
      {showVirtualKeyboard && (
        <div className="virtual-keyboard">
          {/* ... rest of the code ... */}
        </div>
      )}
      <ContactFormModal isOpen={contactModalOpen} onClose={closeContactModal} />
    </div>
  );
};

export default Login;
￼Enter
