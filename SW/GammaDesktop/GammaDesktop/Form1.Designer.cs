
namespace GammaDesktop
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.port_select = new System.Windows.Forms.ComboBox();
            this.uart_conn_btn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.set_date_time = new System.Windows.Forms.Button();
            this.set_det_voltage = new System.Windows.Forms.Button();
            this.version = new System.Windows.Forms.Label();
            this.date_time = new System.Windows.Forms.Label();
            this.detector_voltage = new System.Windows.Forms.Label();
            this.detector_params = new System.Windows.Forms.Label();
            this.start_meas = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.measurment_time = new System.Windows.Forms.Label();
            this.current_time = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.det_voltage = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.write_detector_param = new System.Windows.Forms.Button();
            this.det_coeff_1 = new System.Windows.Forms.TextBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.crystal_type = new System.Windows.Forms.ComboBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // port_select
            // 
            this.port_select.FormattingEnabled = true;
            this.port_select.Location = new System.Drawing.Point(184, 12);
            this.port_select.Name = "port_select";
            this.port_select.Size = new System.Drawing.Size(121, 21);
            this.port_select.TabIndex = 0;
            // 
            // uart_conn_btn
            // 
            this.uart_conn_btn.Location = new System.Drawing.Point(211, 43);
            this.uart_conn_btn.Name = "uart_conn_btn";
            this.uart_conn_btn.Size = new System.Drawing.Size(75, 23);
            this.uart_conn_btn.TabIndex = 1;
            this.uart_conn_btn.Text = "Connect";
            this.uart_conn_btn.UseVisualStyleBackColor = true;
            this.uart_conn_btn.Click += new System.EventHandler(this.uart_conn_btn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(42, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Version";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Time";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 119);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(87, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Detector Voltage";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 179);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(104, 13);
            this.label4.TabIndex = 5;
            this.label4.Text = "Detector Parameters";
            // 
            // set_date_time
            // 
            this.set_date_time.Location = new System.Drawing.Point(211, 299);
            this.set_date_time.Name = "set_date_time";
            this.set_date_time.Size = new System.Drawing.Size(75, 23);
            this.set_date_time.TabIndex = 7;
            this.set_date_time.Text = "Set";
            this.set_date_time.UseVisualStyleBackColor = true;
            // 
            // set_det_voltage
            // 
            this.set_det_voltage.Location = new System.Drawing.Point(211, 383);
            this.set_det_voltage.Name = "set_det_voltage";
            this.set_det_voltage.Size = new System.Drawing.Size(75, 23);
            this.set_det_voltage.TabIndex = 9;
            this.set_det_voltage.Text = "Set";
            this.set_det_voltage.UseVisualStyleBackColor = true;
            // 
            // version
            // 
            this.version.AutoSize = true;
            this.version.Location = new System.Drawing.Point(12, 43);
            this.version.Name = "version";
            this.version.Size = new System.Drawing.Size(10, 13);
            this.version.TabIndex = 10;
            this.version.Text = "-";
            // 
            // date_time
            // 
            this.date_time.AutoSize = true;
            this.date_time.Location = new System.Drawing.Point(12, 93);
            this.date_time.Name = "date_time";
            this.date_time.Size = new System.Drawing.Size(10, 13);
            this.date_time.TabIndex = 11;
            this.date_time.Text = "-";
            // 
            // detector_voltage
            // 
            this.detector_voltage.AutoSize = true;
            this.detector_voltage.Location = new System.Drawing.Point(12, 150);
            this.detector_voltage.Name = "detector_voltage";
            this.detector_voltage.Size = new System.Drawing.Size(10, 13);
            this.detector_voltage.TabIndex = 12;
            this.detector_voltage.Text = "-";
            // 
            // detector_params
            // 
            this.detector_params.AutoSize = true;
            this.detector_params.Location = new System.Drawing.Point(12, 210);
            this.detector_params.Name = "detector_params";
            this.detector_params.Size = new System.Drawing.Size(10, 13);
            this.detector_params.TabIndex = 13;
            this.detector_params.Text = "-";
            // 
            // start_meas
            // 
            this.start_meas.Location = new System.Drawing.Point(171, 93);
            this.start_meas.Name = "start_meas";
            this.start_meas.Size = new System.Drawing.Size(144, 23);
            this.start_meas.TabIndex = 14;
            this.start_meas.Text = "Start Measure";
            this.start_meas.UseVisualStyleBackColor = true;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(168, 131);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(97, 13);
            this.label5.TabIndex = 15;
            this.label5.Text = "Measurement Time";
            // 
            // measurment_time
            // 
            this.measurment_time.AutoSize = true;
            this.measurment_time.Location = new System.Drawing.Point(168, 150);
            this.measurment_time.Name = "measurment_time";
            this.measurment_time.Size = new System.Drawing.Size(10, 13);
            this.measurment_time.TabIndex = 16;
            this.measurment_time.Text = "-";
            // 
            // current_time
            // 
            this.current_time.AutoSize = true;
            this.current_time.Location = new System.Drawing.Point(202, 283);
            this.current_time.Name = "current_time";
            this.current_time.Size = new System.Drawing.Size(10, 13);
            this.current_time.TabIndex = 17;
            this.current_time.Text = "-";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(229, 268);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(30, 13);
            this.label7.TabIndex = 18;
            this.label7.Text = "Time";
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // det_voltage
            // 
            this.det_voltage.FormattingEnabled = true;
            this.det_voltage.Items.AddRange(new object[] {
            "27V",
            "30V",
            "33V",
            "36V",
            ""});
            this.det_voltage.Location = new System.Drawing.Point(186, 356);
            this.det_voltage.Name = "det_voltage";
            this.det_voltage.Size = new System.Drawing.Size(121, 21);
            this.det_voltage.TabIndex = 19;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(18, 236);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(289, 13);
            this.label6.TabIndex = 20;
            this.label6.Text = "_______________________________________________";
            // 
            // write_detector_param
            // 
            this.write_detector_param.Location = new System.Drawing.Point(15, 383);
            this.write_detector_param.Name = "write_detector_param";
            this.write_detector_param.Size = new System.Drawing.Size(75, 23);
            this.write_detector_param.TabIndex = 21;
            this.write_detector_param.Text = "Write";
            this.write_detector_param.UseVisualStyleBackColor = true;
            // 
            // det_coeff_1
            // 
            this.det_coeff_1.Location = new System.Drawing.Point(16, 321);
            this.det_coeff_1.Name = "det_coeff_1";
            this.det_coeff_1.Size = new System.Drawing.Size(100, 20);
            this.det_coeff_1.TabIndex = 22;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(15, 357);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 20);
            this.textBox1.TabIndex = 23;
            // 
            // crystal_type
            // 
            this.crystal_type.FormattingEnabled = true;
            this.crystal_type.Items.AddRange(new object[] {
            "BC412",
            "BC408",
            "LYSO",
            "LSO",
            "BGO",
            "Na(Tl)",
            "Cs(Ti)"});
            this.crystal_type.Location = new System.Drawing.Point(16, 283);
            this.crystal_type.Name = "crystal_type";
            this.crystal_type.Size = new System.Drawing.Size(121, 21);
            this.crystal_type.TabIndex = 24;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(18, 267);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(65, 13);
            this.label8.TabIndex = 25;
            this.label8.Text = "Crystal Type";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(18, 307);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(84, 13);
            this.label9.TabIndex = 26;
            this.label9.Text = "Detector coeff 1";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(18, 344);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(84, 13);
            this.label10.TabIndex = 27;
            this.label10.Text = "Detector coeff 2";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(317, 450);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.crystal_type);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.det_coeff_1);
            this.Controls.Add(this.write_detector_param);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.det_voltage);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.current_time);
            this.Controls.Add(this.measurment_time);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.start_meas);
            this.Controls.Add(this.detector_params);
            this.Controls.Add(this.detector_voltage);
            this.Controls.Add(this.date_time);
            this.Controls.Add(this.version);
            this.Controls.Add(this.set_det_voltage);
            this.Controls.Add(this.set_date_time);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.uart_conn_btn);
            this.Controls.Add(this.port_select);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "GammaDesktop";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.ComboBox port_select;
        private System.Windows.Forms.Button uart_conn_btn;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button set_date_time;
        private System.Windows.Forms.Button set_det_voltage;
        private System.Windows.Forms.Label version;
        private System.Windows.Forms.Label date_time;
        private System.Windows.Forms.Label detector_voltage;
        private System.Windows.Forms.Label detector_params;
        private System.Windows.Forms.Button start_meas;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label measurment_time;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Timer timer1;
        public System.Windows.Forms.Label current_time;
        private System.Windows.Forms.ComboBox det_voltage;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button write_detector_param;
        private System.Windows.Forms.TextBox det_coeff_1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.ComboBox crystal_type;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
    }
}

