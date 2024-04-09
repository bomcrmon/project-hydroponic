import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs';


@Injectable({
  providedIn: 'root'
})
export class LineMessageService {

  private readonly LINE_API_URL = 'https://api.line.me/v2/bot/message/push';
  private readonly LINE_ACCESS_TOKEN = 'h3nqK7pBLQWZe3dXbZEV0jtS9JvHI02pb6F43e14OuU';
  private lineNotifyAPI = 'https://notify-api.line.me/api/notify';



  constructor(private http: HttpClient) { }

  sendMessage(message: string, userId: string): void {
    const headers = {
      'Content-Type': 'application/json',
      'Authorization': `Bearer ${this.LINE_ACCESS_TOKEN}`
    };

    const body = new URLSearchParams();
    body.set('message', message);

    this.http.post(this.lineNotifyAPI, body.toString(), { headers });

    const data = {
      to: userId,
      messages: [
        {
          type: 'text',
          text: message
        }
      ]
    };

    // this.http.post(this.LINE_API_URL, data, { headers })
    //   .subscribe(
    //     response => console.log('Message sent:', response),
    //     error => console.error('Error sending message:', error)
    //   );
  }



    
  }

  


