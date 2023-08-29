import React from 'react';

const ContactFormPage = () => {
  return (
    <div style={{ textAlign: 'center' }}>
      <h2 style={{ marginTop: '20px' }}>Contact Us</h2>
      <div style={{ display: 'flex', justifyContent: 'center', marginTop: '20px' }}>
        <div style={{ flex: 1 }}>
          <div style={{ display: 'flex', alignItems: 'center', marginBottom: '10px' }}>
            <div style={{ marginRight: '10px' }}>
              <img src="phone-logo.png" alt="Phone Logo" width="30" height="30" />
            </div>
            <div>
              <p>By Phone</p>
              <p>1234-567-789</p>
            </div>
          </div>
        </div>
        <div style={{ flex: 1 }}>
          <div style={{ display: 'flex', alignItems: 'center', marginBottom: '10px' }}>
            <div style={{ marginRight: '10px' }}>
              <img src="email-logo.png" alt="Email Logo" width="30" height="30" />
            </div>
            <div>
              <p>By E-mail</p>
              <p>HelpDesk@sc.com</p>
            </div>
          </div>
        </div>
        <div style={{ flex: 1 }}>
          <div style={{ display: 'flex', alignItems: 'center', marginBottom: '10px' }}>
            <div style={{ marginRight: '10px' }}>
              <img src="chat-logo.png" alt="Chat Logo" width="30" height="30" />
            </div>
            <div>
              <p>Live Chat</p>
              <button>Start Chat</button>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}

export default ContactFormPage;
