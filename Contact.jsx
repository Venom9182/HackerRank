import React from 'react';
import './ContactFormModal.css'; // Import your CSS file

const ContactFormModal = ({ isOpen, onClose }) => {
  if (!isOpen) {
    return null;
  }

  return (
    <div className="modal-background">
      <div className="modal-content">
        <span className="close-button" onClick={onClose}>
          &times;
        </span>
        <h2>Contact Us</h2>
        <p>Email: HelpDesk@sc.com</p>
        <p>Phone: 123-456-7890</p>
      </div>
    </div>
  );
};

export default ContactFormModal;
￼Enter
