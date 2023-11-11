using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GammaDesktop
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            port_select.Items.Clear();
            string[] ports = System.IO.Ports.SerialPort.GetPortNames();
            port_select.Items.AddRange(ports);
            current_time.Text = DateTime.Now.ToString();
            
        }

        private void uart_conn_btn_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                serialPort1.BaudRate = 9600;
                serialPort1.DataBits = 8;
                serialPort1.StopBits = System.IO.Ports.StopBits.One;
                serialPort1.Parity = System.IO.Ports.Parity.None;
                serialPort1.Handshake = System.IO.Ports.Handshake.None;
                serialPort1.PortName = port_select.Text;
                serialPort1.Open();
                //serialPort1.Write("0");
                uart_conn_btn.Text = "Disconnect";
            }
            else
            {
                uart_conn_btn.Text = "Connect";
                serialPort1.Close();
            }
        }
    }
}
