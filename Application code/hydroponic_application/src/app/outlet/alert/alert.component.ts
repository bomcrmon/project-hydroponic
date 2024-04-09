import { Component, OnInit } from '@angular/core';
import {
  MatDialog,
  MatDialogRef,
  MAT_DIALOG_DATA,
} from '@angular/material/dialog';
@Component({
  selector: 'app-alert',
  templateUrl: './alert.component.html',
  styleUrls: ['./alert.component.css'],
})
export class AlertComponent {
  show = false;

  data: any = {
    title: '',
    textBody: '',
    status: '',
    textButton: '',
    confirmButton: false,
    cancleButton: false,
    cancleButtonText: 'ยกเลิก',
  };

  imgStatus = '';
  textStatus = '';
  headClass = '';
  btnClass = '';

  constructor(public dialogRef: MatDialogRef<AlertComponent>) {
    dialogRef.disableClose = true;
  }
  ngOnInit(): void {
    if (this.data.confirmButton) {
      this.data.cancleButton = true;
    }

    if (!this.data.cancleButtonText) {
      this.data.cancleButtonText = 'ยกเลิก';
    }
    this.getclass(this.data.status);
  }
  
  submit(): void {
    this.dialogRef.close({
      isResult: true,
    });
  }

  cancel(): void {
    this.dialogRef.close({
      isResult: false,
    });
  }

  getclass(status: any) {
    if (status == 'success') {
      this.imgStatus = '../../../../assets/imgs/checked 1.png';
      this.textStatus = 'text-transection text-complete';
      this.headClass = 'modal-header-bg-success';
    } else if (status == 'error') {
      this.imgStatus = '../../../../assets/imgs/cancel 1.png';
      this.textStatus = 'text-transection text-cancle';
      this.headClass = 'modal-header-bg-error';
    } else {
      this.imgStatus = '../../../../assets/imgs/delete 1.png';
      this.textStatus = 'text-transection text-cancle';
      this.btnClass = 'modal-alert-btn-black';
      this.headClass = 'modal-header-bg-light';
    }
  }
}
